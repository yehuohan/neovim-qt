#include "plugin_manager.h"

#include <QApplication>
#include <QDir>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPluginLoader>
#include <QJsonObject>

namespace NeovimQt {

PluginManager::PluginManager (NeovimConnector *nvim, QWidget *parent)
: QStackedWidget(parent), m_nvim(nvim) {
    if (m_nvim->isReady()) {
        connector_ready_cb();
    }
    connect(m_nvim, &NeovimConnector::ready, this, &PluginManager ::connector_ready_cb);
}

void PluginManager::loadPlugin(const QByteArray& name, const QString& filepath) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (!plug) {
        QDir path(qApp->applicationDirPath());
        path.cd("plugins");
        QPluginLoader* loader = new QPluginLoader(path.absoluteFilePath(filepath));
        QObject *obj = loader->instance();
        if (obj) {
            QJsonObject json = loader->metaData().value("MetaData").toObject();
            plug = qobject_cast<PluginInterface *>(obj);
            if (plug) {
                m_plugs.insert(name, plug);
                m_loaders.insert(name, loader);
                plug->init(m_nvim->neovimObject());
                addWidget(plug->widget());
                setCurrentWidget(plug->widget());
                setVisible(true);
            }
        }
    }
}

void PluginManager::unloadPlugin(const QByteArray& name) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (plug) {
        if (count() == 1) {
            setVisible(false);
        }
        removeWidget(plug->widget());
        QPluginLoader* loader = m_loaders.value(name);
        plug->free();
        loader->unload();
        m_plugs.remove(name);
        m_loaders.remove(name);
    }
}

void PluginManager::showPlugin(const QByteArray& name) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (plug) {
        setVisible(true);
        setCurrentWidget(plug->widget());
    }
}

void PluginManager::hidePlugin(const QByteArray& name) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (plug) {
        int index = indexOf(plug->widget());
        if (count() == 1) {
            setVisible(false);
        } else {
            setCurrentIndex((index + 1) % count());
        }
    }
}

void PluginManager::nofityPlugin(const QByteArray& name, const QVariantList& args) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (plug) {
        plug->handleNeovimNotification(args);
    }
}

void PluginManager ::connector_ready_cb() {
    connect(m_nvim->neovimObject(), &NeovimApi1::neovimNotification, this,
            &PluginManager::handleNeovimNotification);

    m_nvim->neovimObject()->vim_subscribe("Plugin");
}

void PluginManager::handleNeovimNotification(const QByteArray &name,
                    const QVariantList &args) {
    if (name == "Plugin") {
        if (args.size() < 2) {
            return;
        }
        // [ name, action, pluginname, ... ]
        QByteArray action = args.at(0).toByteArray();
        QByteArray plugname = args.at(1).toByteArray();
        if (action == "Load") {
            QString filepath = args.at(2).toString();
            loadPlugin(plugname, filepath);
        } else if (action == "Unload") {
            unloadPlugin(plugname);
        } else if (action == "Show") {
            showPlugin(plugname);
        } else if (action == "Hide") {
            hidePlugin(plugname);
        } else if (action == "Notify") {
            QVariantList plugargs = args.at(2).toList();
            nofityPlugin(plugname, plugargs);
        }
    }
}

}  // namespace NeovimQt

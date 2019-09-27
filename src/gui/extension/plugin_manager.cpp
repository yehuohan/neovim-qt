#include "plugin_manager.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include "treeview.h"

namespace NeovimQt {

PluginManager::PluginManager (NeovimConnector *nvim, QWidget *parent)
: QStackedWidget(parent), m_nvim(nvim) {

    if (m_nvim->isReady()) {
        connector_ready_cb();
    }
    connect(m_nvim, &NeovimConnector::ready, this, &PluginManager ::connector_ready_cb);
}

PluginInterface* PluginManager::build(const QByteArray& name) {
    if (name == "TreeView") {
        return new TreeView();
    } else if (name == "Debugger") {
    }
    return nullptr;
}

void PluginManager::loadPlugin(const QByteArray& name) {
    PluginInterface* plug = m_plugs.value(name, nullptr);
    if (!plug) {
        plug = build(name);
        if (plug) {
            plug->init(m_nvim);
            addWidget(plug->widget());
            m_plugs.insert(name, plug);
            setVisible(true);
            setCurrentWidget(plug->widget());
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
        m_plugs.remove(name);
        delete plug;
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
        // ['Plugin', 'Load...', 'PlugName', ...]
        QByteArray action = args.at(0).toByteArray();
        QByteArray plugname = args.at(1).toByteArray();
        if (action == "Load") {
            loadPlugin(plugname);
        } else if (action == "Unload") {
            unloadPlugin(plugname);
        } else if (action == "Show") {
            showPlugin(plugname);
        } else if (action == "Hide") {
            hidePlugin(plugname);
        }
    }
}

}  // namespace NeovimQt

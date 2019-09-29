#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <QWidget>
#include <QStackedWidget>
#include <QHash>
#include <QByteArray>
#include <QString>
#include <QPluginLoader>
#include "plugin_interface.h"
#include "neovimconnector.h"

namespace NeovimQt {

class PluginManager : public QStackedWidget {
    Q_OBJECT
public:
    PluginManager(NeovimConnector *, QWidget *parent = 0);
    void loadPlugin(const QByteArray& name, const QString& filepath);
    void unloadPlugin(const QByteArray& name);
    void showPlugin(const QByteArray& name);
    void hidePlugin(const QByteArray& name);
    void nofityPlugin(const QByteArray& name, const QVariantList& args);

public slots:
    void handleNeovimNotification(const QByteArray &, const QVariantList &);
    void connector_ready_cb();

protected:
    NeovimConnector *m_nvim;
    QHash<QByteArray, QPluginLoader*> m_loaders;
    QHash<QByteArray, PluginInterface*> m_plugs;
};

}  // namespace NeovimQt

#endif // PLUGIN

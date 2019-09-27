#ifndef PLUGIN_MANAGER
#define PLUGIN_MANAGER

#include <QWidget>
#include <QStackedWidget>
#include <QHash>
#include <QByteArray>
#include <QString>
#include "plugin_interface.h"
#include "neovimconnector.h"

namespace NeovimQt {

class PluginManager : public QStackedWidget {
    Q_OBJECT
public:
    PluginManager(NeovimConnector *, QWidget *parent = 0);
    void loadPlugin(const QByteArray& name);
    void unloadPlugin(const QByteArray& name);
    void showPlugin(const QByteArray& name);
    void hidePlugin(const QByteArray& name);

public slots:
    void handleNeovimNotification(const QByteArray &, const QVariantList &);
    void connector_ready_cb();

private:
    PluginInterface* build(const QByteArray& name);

protected:
    NeovimConnector *m_nvim;
    QHash<QByteArray, PluginInterface*> m_plugs;
};

}  // namespace NeovimQt

#endif // PLUGIN

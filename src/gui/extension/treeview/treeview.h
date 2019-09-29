#ifndef TREEVIEW
#define TREEVIEW

#include <QFileSystemModel>
#include <QTreeView>
#include <QUrl>
#include <QVariantList>
#include "plugin_interface.h"

namespace NeovimQt {

class TreeView : public QTreeView, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "treeview.json")
    Q_INTERFACES(NeovimQt::PluginInterface)

 public:
    QWidget* widget() { return this; };
    void init();

 public slots:
    void open(const QModelIndex &);
    void setDirectory(const QString &, bool notify = true);
    void handleNeovimNotification(const QVariantList &);

 protected:
    QFileSystemModel *model;
};

}  // namespace NeovimQt

#endif  // TREEVIEW

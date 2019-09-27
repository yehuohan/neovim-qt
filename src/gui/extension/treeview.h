#ifndef TREEVIEW
#define TREEVIEW

#include <QFileSystemModel>
#include <QTreeView>
#include <QUrl>
#include "plugin_interface.h"
#include "neovimconnector.h"

namespace NeovimQt {

class TreeView : public QTreeView, public PluginInterface {
    Q_OBJECT

 public:
    QWidget* widget() { return this; };
    void init(NeovimConnector*);
    void free() {};

 public slots:
	void open(const QModelIndex &);
	void setDirectory(const QString &, bool notify = true);
	void handleNeovimNotification(const QByteArray &, const QVariantList &);
	void connector_ready_cb();

 protected:
	QFileSystemModel *model;
	NeovimConnector *m_nvim;
};

}  // namespace NeovimQt

#endif  // TREEVIEW

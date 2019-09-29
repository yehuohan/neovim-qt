#include "treeview.h"

#include <QDir>
#include <QHeaderView>
#include <QKeyEvent>
#include <QProcess>
#include <QStandardPaths>

static const int MAX_COLUMNS_ON_INIT = 10;

namespace NeovimQt {
void TreeView::init() {
	model = new QFileSystemModel(this);
	setModel(model);
	header()->hide();

	for (int i = 1; i < MAX_COLUMNS_ON_INIT; i++) {
		hideColumn(i);
	}

	connect(this, &TreeView::doubleClicked, this, &TreeView::open);
}

void TreeView::open(const QModelIndex &index) {
	QFileInfo info = model->fileInfo(index);
	if (info.isFile() && info.isReadable()) {
		QVariantList args;
		args << info.filePath();
        this->nvim_call_function("GuiDrop", args);
	}
	focusNextChild();
}

void TreeView::setDirectory(const QString &dir, bool notify) {
	if (QDir(dir).exists()) {
		QDir::setCurrent(dir);
		model->setRootPath(dir);
		setRootIndex(model->index(dir));
		if (notify) {
            this->nvim_command(QByteArray::fromStdString("cd " + dir.toStdString()));
		}
	}
}

void TreeView::handleNeovimNotification(const QVariantList &args) {
    if (args.size() <= 0) {
        return;
    }
    QByteArray name = args.at(0).toByteArray();
	if (name == "Dir" && args.size() >= 2) {
        //setDirectory(m_nvim->decode(args.at(1).toByteArray()), false);
        setDirectory(args.at(1).toString(), false);
	}
}

}  // namespace NeovimQt

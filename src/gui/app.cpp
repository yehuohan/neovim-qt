#include "app.h"

#include <QFileOpenEvent>
#include <QIcon>

namespace NeovimQt {

App::App(int &argc, char ** argv)
:QApplication(argc, argv)
{
	setApplicationDisplayName("Neovim");
	setWindowIcon(QIcon(":/neovim.png"));
}

bool App::event(QEvent *event)
{
	if( event->type()  == QEvent::FileOpen) {
		QFileOpenEvent * fileOpenEvent = static_cast<QFileOpenEvent *>(event);
		if(fileOpenEvent) {
			emit openFilesTriggered({fileOpenEvent->url()});
		}
	}
	return QApplication::event(event);
}

} // Namespace

#ifndef DEBUGGER
#define DEBUGGER

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "plugin_interface.h"
#include "neovimconnector.h"

namespace NeovimQt {

class DebuggerBar : public QToolBar {
    Q_OBJECT
public:
    DebuggerBar(QWidget* parent = 0);

private:
    QAction m_run;
    QAction m_stop;
    QAction m_reset;
    QAction m_step_over;
    QAction m_step_into;
    QAction m_step_out;
};

class Debugger : public QWidget, public PluginInterface {
    Q_OBJECT
public:
    QWidget* widget() { return this; };
    void init(NeovimConnector*);
    void free() {};

private:
    DebuggerBar* m_bar;
};

}  // namespace NeovimQt

#endif // DEBUGGER

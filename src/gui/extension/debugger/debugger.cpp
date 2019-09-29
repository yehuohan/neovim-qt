#include "debugger.h"

#include <QVBoxLayout>

namespace NeovimQt {

DebuggerBar::DebuggerBar(QWidget* parent) {
    m_run.setIcon(QIcon(":icons/run.png"));
    m_stop.setIcon(QIcon(":icons/stop.png"));
    m_reset.setIcon(QIcon(":icons/reset.png"));
    m_step_over.setIcon(QIcon(":icons/stepover.png"));
    m_step_into.setIcon(QIcon(":icons/stepinto.png"));
    m_step_out.setIcon(QIcon(":icons/stepout.png"));

    addAction(&m_run);
    addAction(&m_stop);
    addAction(&m_reset);
    addAction(&m_step_over);
    addAction(&m_step_into);
    addAction(&m_step_out);
}

void Debugger::init(NeovimConnector* nvim) {
    m_bar = new DebuggerBar(this);
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    layout->addWidget(m_bar);
    layout->setMargin(0);
    layout->setSpacing(0);
}

}  // namespace NeovimQt

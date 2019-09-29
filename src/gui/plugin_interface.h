#ifndef PLUGIN_INTERFACE
#define PLUGIN_INTERFACE

#include <QWidget>
#include <QByteArray>
#include <QVariantList>
#include <functional>
#include "neovimapi1.h"

namespace NeovimQt {

class PluginInterface {
public:
    virtual ~PluginInterface() {}
    virtual QWidget* widget() = 0;
    void init(NeovimApi1* api) {
        this->nvim_command = std::bind(&NeovimApi1::nvim_command, api, std::placeholders::_1);
        this->nvim_eval = std::bind(&NeovimApi1::nvim_eval, api, std::placeholders::_1);
        this->nvim_call_function = std::bind(&NeovimApi1::nvim_call_function, api, std::placeholders::_1, std::placeholders::_2);
        this->init();
    };
    virtual void free() {};
    virtual void handleNeovimNotification(const QVariantList &) {};

protected:
    virtual void init() {};
    std::function<MsgpackRequest*(QByteArray)> nvim_command;
    std::function<MsgpackRequest*(QByteArray)> nvim_eval;
    std::function<MsgpackRequest*(QByteArray, QVariantList)> nvim_call_function;
};

}  // namespace NeovimQt

#define  PluginInterface_iid "neovim.qt.PluginInterface"
Q_DECLARE_INTERFACE(NeovimQt::PluginInterface, PluginInterface_iid)

#endif // PLUGIN_INTERFACE

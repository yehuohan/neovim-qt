#ifndef PLUGIN_INTERFACE
#define PLUGIN_INTERFACE

#include <QWidget>
#include "neovimconnector.h"

namespace NeovimQt {

class PluginInterface {
public:
    virtual ~PluginInterface(){}
    virtual QWidget* widget() = 0;
    virtual void init(NeovimConnector*) {};
    virtual void free() {};
};

}  // namespace NeovimQt

#endif // PLUGIN_INTERFACE

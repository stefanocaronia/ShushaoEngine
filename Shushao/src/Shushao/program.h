#pragma once

#include "component.h"
#include "core.h"

namespace se {

class SHUSHAO_API Program : public Component {
public:
    virtual void setup() { name = "Program"; }
    ~Program();

protected:
private:
};

}  // namespace se

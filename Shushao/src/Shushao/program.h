#pragma once

#include "component.h"
#include "Core.h"
#include "sepch.h"

namespace se {

class SHUSHAO_API Program : public Component {
public:
    virtual void setup() { name = "Program"; }
    ~Program();

protected:
private:
};

}  // namespace se

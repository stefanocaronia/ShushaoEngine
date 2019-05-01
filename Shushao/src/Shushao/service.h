#pragma once

#include "Core.h"
#include "object.h"

namespace se {

class SHUSHAO_API Service : public Object {
public:
    Service();
    virtual ~Service();

    bool active;

    virtual void Init();
    virtual void Update();
    virtual void Exit();

protected:
private:
};

}  // namespace se

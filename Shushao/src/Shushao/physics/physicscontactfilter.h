#pragma once

namespace se {

class PhysicsContactFilter {
public:
    PhysicsContactFilter();
    ~PhysicsContactFilter() {
        if (impl) delete impl;
    }

    class Impl;  // Pimpl!
    Impl* impl;
};

}  // namespace se

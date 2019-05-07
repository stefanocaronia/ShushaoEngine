#include <Box2D/Box2D.h>

#include "Physics.h"

namespace se {

class Physics::Impl {
public:
    static b2World* world;
    static b2Vec2 gravity;
};

}
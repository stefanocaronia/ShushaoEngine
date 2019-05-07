#pragma once

#include <Box2D/Box2D.h>

#include "Rigidbody2d.h"

namespace se {

struct Rigidbody2D::Impl {
    b2Body* body = nullptr;
    b2BodyDef bodyDef;
};

}  // namespace se

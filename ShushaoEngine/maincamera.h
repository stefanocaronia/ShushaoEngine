# pragma once

#include "gllibs.h"
#include "entity.h"
#include "camera.h"

using namespace ShushaoEngine;

class MainCamera : public Entity {
	public:
		MainCamera();
		~MainCamera();

		Camera* camera;

	protected:

	private:
};

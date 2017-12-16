# pragma once

#include "entity.h"
#include "camera.h"

class MainCamera : public ShushaoEngine::Entity {
	public:
		MainCamera();
		~MainCamera();

		ShushaoEngine::Camera* camera;

	protected:

	private:
};

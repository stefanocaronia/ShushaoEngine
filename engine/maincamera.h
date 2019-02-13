# pragma once

#include "entity.h"
#include "camera.h"

class MainCamera : public se::Entity {
	public:
		MainCamera();
		~MainCamera();

		se::Camera* camera;

	protected:

	private:
};

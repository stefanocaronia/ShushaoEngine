# pragma once

#include "libs.h"
#include "gameobject.h"
#include "camera.h"

using namespace ShushaoEngine;

class MainCamera : public GameObject {
	public:
		MainCamera();
		~MainCamera();

		Camera* camera;

	protected:

	private:
};

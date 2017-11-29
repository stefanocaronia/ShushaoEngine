#pragma once

#include <glm/glm.hpp>

#include "component.h"
#include "color.h"
#include "rect.h"
#include "macros.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class Camera : public Component {

		public:

			Camera();

			Color backgroundColor;

			// mat4 worldToCameraMatrix; // TODO? Matrix that transforms from world to camera space.
			// mat4 cameraToWorldMatrix; // TODO?

			mat4 View;
			mat4 Projection;

			// methods
			mat4 getViewMatrix();
			mat4 getProjectionMatrix();
			void setDepth(float);
			void setOrthographic(bool);
			void setOrthographicSize(float);
			void setFieldOfView(float);
			void setFarClipPlane(float);
			void setNearClipPlane(float);
			void setRect(Rect);
			float getDepth();
			bool getOrthographic();
			float getOrthographicSize();
			float getFieldOfView();
			float getFarClipPlane();
			float getNearClipPlane();
			Rect getRect();

			void print();

		private:

			float aspect;
			bool orthographic = true;
			float orthographicSize = 5.0f;
			float depth = 3.0f;
			float fieldOfView = 45.0f;
			float farClipPlane = 1000.0f;
			float nearClipPlane = 3.0f;

			Rect rect;	// Where on the screen is the camera rendered in normalized coordinates.

	};

}

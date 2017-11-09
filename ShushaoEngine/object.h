#pragma once

#include <string>
#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>
#include <glm.hpp>

#include "object.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class Transform;

	class Object {

		public:

			Object();
			virtual ~Object();

			int InstanceID = 0;

			string name;

			string ToString();

			static void Destroy(Object*, float);
			static void Destroy(Object*);

			int GetInstanceID();

			static Object* Instantiate(Object*);
			static Object* Instantiate(Object*, Transform*);
			static Object* Instantiate(Object*, Transform*, bool);
			static Object* Instantiate(Object*, vec3, quat);
			static Object* Instantiate(Object*, vec3, quat, Transform*);



	};

}

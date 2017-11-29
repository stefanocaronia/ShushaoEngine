#pragma once

#include <glm/glm.hpp>
#include <string>

#include "object.h"

namespace ShushaoEngine {

	using namespace std;
	using namespace glm;

	class Transform;

	class Object {

		public:

			Object();
			Object(string);
			virtual ~Object();

			int InstanceID = 0;

			string name;

			string ToString();

			static void Destroy(Object*, float);
			static void Destroy(Object*);

			int GetInstanceID();

			bool operator==(const char*);
			bool operator==(const Object&);

			static Object* Instantiate(Object*);
			static Object* Instantiate(Object*, Transform*);
			static Object* Instantiate(Object*, Transform*, bool);
			static Object* Instantiate(Object*, vec3, quat);
			static Object* Instantiate(Object*, vec3, quat, Transform*);


	};

}

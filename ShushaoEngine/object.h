#pragma once

#include <glm/glm.hpp>
#include <string>

namespace ShushaoEngine {

	class Transform;

	class Object {

		public:

			Object();
			Object(std::string);
			virtual ~Object();

			int InstanceID = 0;

			std::string name;

			std::string ToString();

			static void Destroy(Object*, float);
			static void Destroy(Object*);

			int GetInstanceID();

			bool operator==(const char*);
			bool operator==(const Object&);

			static Object* Instantiate(Object*);
			static Object* Instantiate(Object*, Transform*);
			static Object* Instantiate(Object*, Transform*, bool);
			static Object* Instantiate(Object*, glm::vec3, glm::quat);
			static Object* Instantiate(Object*, glm::vec3, glm::quat, Transform*);


	};

}

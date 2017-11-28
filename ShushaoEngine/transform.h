#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/euler_angles.hpp>

#include "component.h"
#include "entity.h"

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	class Transform;

	class Transform : public Component {

		public:

			Transform();

			bool isRoot = false;

			Transform* parent = nullptr;
			vector<Transform*> children;

			vec3 localPosition = VEC3_ZERO;
			quat localRotation = QUATERNION_IDENTITY;
			vec3 localScale = VEC3_IDENTITY;

			// readonly properties
			const vec3& position = _position;
			const quat& rotation = _rotation;
			const vec3& scale = _scale;
			const vec3& pivot = _pivot;
			const mat4& M = _M;
			const mat4& MVP = _MVP;
			const vec3& forward = _forward;
			const vec3& right = _right;
			const vec3& up = _up;

			static const vec3 VEC3_ZERO;
			static const vec3 VEC3_IDENTITY;
			static const vec3 VEC3_IDENTITY2D;
			static const vec3 UP;
			static const vec3 DOWN;
			static const vec3 FORWARD;
			static const vec3 BACK;
			static const vec3 RIGHT;
			static const vec3 LEFT;
			static const quat QUATERNION_IDENTITY;

			// methods
			Transform* getParent();
			void setParent(Transform*, bool worldPositionStays = false);
			void RemoveChild(Transform* t);
			void AddChild(Transform* t);
			bool hasParent();
			bool hasRootParent();
			bool isChild();
			bool onRoot();

			mat4 getLocalToParentMatrix();
			mat4 getLocalToWorldMatrix();
			mat4 getWorldToLocalMatrix();
			vec3 toWorld(vec3);

			// lifecycle
			void Awake();
			void Update();

			//{ #region getter and setters

			vec3 getEulerAngles();
			vec3 getLocalEulerAngles();

			Transform* getChild(unsigned int);

			void setPivot(vec2);
			void setPosition(vec3);
			void setLocalPosition(vec3);
			void setLocalRotation(quat);
			void setLocalRotation(vec3);
			void setLocalScale(vec3);

			//}

		private:

			bool lock = false;

			vec3 _position = VEC3_ZERO;
			quat _rotation = QUATERNION_IDENTITY;
			vec3 _scale = VEC3_IDENTITY2D;

			vec3 _forward = {0.0f, 0.0f, 1.0f};
			vec3 _right = {1.0f, 0.0f, 0.0f};
			vec3 _up = {0.0f, 1.0f, 0.0f};

			vec3 _pivot = VEC3_ZERO;
			mat4 _M = mat4();
			mat4 _MVP = mat4();

			void setupDirections();
	};

}

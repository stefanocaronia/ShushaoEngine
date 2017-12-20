#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "component.h"
#include "constants.h"

namespace ShushaoEngine {

	class Transform;

	class Transform : public Component {

		public:

			Transform();

			bool isRoot = false;

			Transform* parent = nullptr;
			std::vector<Transform*> children;

			glm::vec3 localPosition = VEC3_ZERO;
			glm::quat localRotation = QUATERNION_IDENTITY;
			glm::vec3 localScale = VEC3_IDENTITY;

			// readonly properties
			const glm::vec3& position = _position;
			const glm::quat& rotation = _rotation;
			const glm::vec3& scale = _scale;
			const glm::vec3& pivot = _pivot;
			const glm::mat4& MVP = _MVP;
			const glm::vec3& forward = _forward;
			const glm::vec3& right = _right;
			const glm::vec3& up = _up;

			// methods
			Transform* getParent();
			Transform* getChild(unsigned int);
			void SetParent(Transform*, bool worldPositionStays = false);
			void RemoveChild(Transform* t);
			void AddChild(Transform* t);
			bool isAtRoot();

			glm::mat4 GetLocalToParentMatrix();
			glm::mat4 GetLocalToWorldMatrix();
			glm::mat4 GetWorldToLocalMatrix();
			glm::vec3 GetWorldPosition();
			glm::vec3 GetWorldScale();
			glm::quat GetWorldOrientation();

			// lifecycle
			void Awake();
			void Update();

			//{ #region getter and setters

			glm::vec3 GetEulerAngles();
			glm::vec3 GetLocalEulerAngles();

			void SetPivot(glm::vec2);
			void SetPosition(glm::vec3);
			void SetLocalPosition(glm::vec3);
			void SetLocalRotation(glm::quat);
			void SetLocalRotation(glm::vec3);
			void SetLocalScale(glm::vec3);
			void SetRotation(glm::quat);
			void SetRotation(glm::vec3);

			//}

			static const glm::vec3 VEC3_ZERO;
			static const glm::vec3 VEC3_IDENTITY;
			static const glm::vec3 VEC3_IDENTITY2D;
			static const glm::vec3 UP;
			static const glm::vec3 X;
			static const glm::vec3 Y;
			static const glm::vec3 Z;
			static const glm::vec3 DOWN;
			static const glm::vec3 FORWARD;
			static const glm::vec3 BACK;
			static const glm::vec3 RIGHT;
			static const glm::vec3 LEFT;
			static const glm::quat QUATERNION_IDENTITY;

		private:

			bool lock = false;

			glm::vec3 _position = VEC3_ZERO;
			glm::quat _rotation = QUATERNION_IDENTITY;
			glm::vec3 _scale = VEC3_IDENTITY2D;
			glm::vec3 _forward = FORWARD;
			glm::vec3 _right = RIGHT;
			glm::vec3 _up = UP;
			glm::vec3 _pivot = VEC3_ZERO;
			glm::mat4 _MVP = glm::mat4();

			void setupDirections();
			void buildMVP();
	};

}

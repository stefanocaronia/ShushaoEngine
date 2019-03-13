#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "component.h"
#include "constants.h"
#include "rect.h"

namespace se {

	class Transform;

	enum class Origin {
		LOCAL,
		WORLD
	};

	namespace PivotPosition {
		const glm::vec2 CENTER 		= {0.5f, 0.5f};
		const glm::vec2 LEFT 		= {0.0f, 0.5f};
		const glm::vec2 RIGHT 		= {1.0f, 0.5f};
		const glm::vec2 TOPLEFT 	= {0.0f, 1.0f};
		const glm::vec2 TOPRIGHT 	= {1.0f, 1.0f};
		const glm::vec2 TOP 		= {0.5f, 1.0f};
		const glm::vec2 BOTTOM 		= {0.5f, 0.0f};
		const glm::vec2 BOTTOMLEFT 	= {0.0f, 0.0f};
		const glm::vec2 BOTTOMRIGHT = {1.0f, 0.0f};
	};

	class Transform : public Component {

		public:

			virtual void setup();

			bool isRoot = false;
			bool isFree = false;

			Origin origin = Origin::LOCAL;

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

			const glm::mat4& localToWorldMatrix = _localToWorldMatrix;
			const glm::mat4& localToParentMatrix = _localToParentMatrix;
			const glm::mat4& worldToLocalMatrix = _worldToLocalMatrix;
			const glm::mat4& rootMatrix = _rootMatrix;

			// methods
			bool isAtRoot();
			Transform* GetParent();
			Transform* GetChild(unsigned int);
			std::vector<Transform*> GetParents();
			void SetParent(Transform*, bool worldPositionStays = false);
			void RemoveChild(Transform* t);
			void AddChild(Transform* t);

			GLfloat* uMVP(); // MVP Matrix for uniforms
			GLfloat* uM(); // Model Matrix for uniforms

			glm::mat4 GetLocalToParentMatrix();
			glm::mat4 GetLocalToWorldMatrix();
			glm::mat4 GetWorldToLocalMatrix();
			glm::mat4 GetRootMatrix();
			glm::vec3 GetWorldPosition();
			glm::vec3 GetLocalPosition(glm::vec3);
			glm::vec3 GetWorldScale();
			glm::quat GetWorldOrientation();

			// lifecycle
			void Awake();
			void Update();
			void Render();

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
			static const glm::vec3 DOWN;
			static const glm::vec3 FORWARD;
			static const glm::vec3 BACK;
			static const glm::vec3 RIGHT;
			static const glm::vec3 LEFT;
			static const glm::quat QUATERNION_IDENTITY;
			static const glm::vec3 AXIS_X;
			static const glm::vec3 AXIS_Y;
			static const glm::vec3 AXIS_Z;

			void Invalidate();


			//{ #region rect transform

			bool rectTransform = false;

			const glm::vec2& anchoredPosition = _anchoredPosition; //The position of the pivot of this RectTransform relative to the anchor reference point.
			const glm::vec3& anchoredPosition3D = _anchoredPosition3D; // The 3D position of the pivot of this RectTransform relative to the anchor reference point.
			const glm::vec2& anchorMax = _anchorMax; // The normalized position in the parent RectTransform that the upper right corner is anchored to.
			const glm::vec2& anchorMin = _anchorMin; // The normalized position in the parent RectTransform that the lower left corner is anchored to.
			const glm::vec2& offsetMax = _offsetMax; // The offset of the upper right corner of the rectangle relative to the upper right anchor.
			const glm::vec2& offsetMin = _offsetMin; //	The offset of the lower left corner of the rectangle relative to the lower left anchor.
			const Rect& rect = _rect; // The calculated rectangle in the local space of the Transform.
			const glm::vec2& sizeDelta = _sizeDelta; //	The size of this RectTransform relative to the distances between the anchors.

			void ForceUpdateRectTransforms(); // Force the recalculation of RectTransforms internal data.
			void GetLocalCorners(); // Get the corners of the calculated rectangle in the local space of its Transform.
			void GetWorldCorners(); // Get the corners of the calculated rectangle in world space.
			void SetInsetAndSizeFromParentEdge(); // Set the distance of this rectangle relative to a specified edge of the parent rectangle, while also setting its size.
			void SetSizeWithCurrentAnchors(); // Makes the RectTransform calculated rect be a given size on the specified axis.

			void SetRect(Rect rect_) {_rect = rect_;}
			void SetRectSize(glm::vec2 size_) {_rect.SetSize(size_);}

			//}

		private:

			bool matrixInvalid = false;
			bool inverseMatrixInvalid = false;

			glm::vec3 _position = VEC3_ZERO;
			glm::quat _rotation = QUATERNION_IDENTITY;
			glm::vec3 _scale = VEC3_IDENTITY2D;
			glm::vec3 _forward = FORWARD;
			glm::vec3 _right = RIGHT;
			glm::vec3 _up = UP;
			glm::vec3 _pivot = VEC3_ZERO;
			glm::mat4 _MVP = glm::mat4();

			glm::mat4 _localToWorldMatrix = glm::mat4();
			glm::mat4 _localToParentMatrix = glm::mat4();
			glm::mat4 _worldToLocalMatrix = glm::mat4();
			glm::mat4 _rootMatrix = glm::mat4();

			void setupDirections();
			void buildMVP();

			//{ #region rect transform

			Rect _rect;
			glm::vec2 _anchoredPosition;
			glm::vec3 _anchoredPosition3D;
			glm::vec2 _anchorMax = {0.5f, 0.5f};
			glm::vec2 _anchorMin = {0.5f, 0.5f};
			glm::vec2 _offsetMax = {0.0f, 0.0f};
			glm::vec2 _offsetMin = {0.0f, 0.0f};
			glm::vec2 _sizeDelta;

			void updateRectTransforms();

			//}
	};

}

#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>

#include "component.h"
#include "glmanager.h"

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	class Transform;

	class Transform : public Component, public vector<Transform*> {

		public:

			Transform();


			Transform* root; // Returns the topmost transform in the hierarchy. (This never returns null, if this Transform doesn't have a parent it returns itself.)

			vec3 position = {0.0f, 0.0f, 0.0f}; // The position of the transform in world space.
			quat rotation;	// The rotation of the transform in world space stored as a Quaternion.
			vec3 lossyScale = {1.0f, 1.0f, 1.0f}; // The global scale of the object (Read Only).

			vec3 eulerAngles; //The rotation as Euler angles in degrees.

			vec3 localPosition = {0.0f, 0.0f, 0.0f};	// Position of the transform relative to the parent transform.
			quat localRotation;	// The rotation of the transform relative to the parent transform's rotation.
			vec3 localScale = {1.0f, 1.0f, 1.0f};	// The scale of the transform relative to the parent.
			vec3 localEulerAngles; // The rotation as Euler angles in degrees relative to the parent transform's rotation.

			mat4x4 localToWorldMatrix;	// Matrix that transforms a point from local space into world space (Read Only).
			mat4x4 worldToLocalMatrix;	// Matrix that transforms a point from world space into local space (Read Only).

			vec3 forward = {0.0f, 0.0f, 1.0f}; // The blue axis of the transform in world space.
			vec3 right = {1.0f, 0.0f, 0.0f}; // The red axis of the transform in world space.
			vec3 up = {0.0f, 1.0f, 0.0f};	// The green axis of the transform in world space.

			GLManager& GL = GLManager::GetInstance();

			glm::mat4 M; // model view matrix
			glm::mat4 MVP; // model view projection matrix

			int childCount;	// TODO:  The number of children the Transform has.

			// hasChanged	// TODO? Has the transform changed since the last time the flag was set to 'false'?
			// hierarchyCapacity // TODO? The transform capacity of the transform's hierarchy data structure.
			int hierarchyCount;	// TODO:  The number of transforms in the transform's hierarchy data structure.

			// cycle

			void updateCycle();
			void renderCycle();
			void fixedUpdateCycle();

			// methods

			Transform* GetParent();	// TODO:  Set the parent of the transform.
			void SetParent(Transform*);	// TODO:  Set the parent of the transform.
			void SetParent(Transform*, bool);	// TODO:  Set the parent of the transform.

			void RemoveChild(Transform* t);
			void AddChild(Transform* t);

			//void DetachChildren();	// TODO: Unparents all children.
			//void Find();	// TODO:  Finds a child by name and returns it.
			//void GetChild();	// TODO:  Returns a transform child by index.
			//void GetSiblingIndex();	// TODO:  Gets the sibling index.
			//void InverseTransformDirection();	// TODO:  Transforms a direction from world space to local space. The opposite of Transform.TransformDirection.
			//void InverseTransformPoint();	// TODO:  Transforms position from world space to local space.
			//void InverseTransformVector();	// TODO:  Transforms a vector from world space to local space. The opposite of Transform.TransformVector.
			//void IsChildOf();	// TODO:  Is this transform a child of parent?
			//void LookAt();	// TODO:  Rotates the transform so the forward vector points at /target/'s current position.
			//void Rotate();	// TODO:  Applies a rotation of eulerAngles.z degrees around the z axis, eulerAngles.x degrees around the x axis, and eulerAngles.y degrees around the y axis (in that order).
			//void RotateAround();	// TODO:  Rotates the transform about axis passing through point in world coordinates by angle degrees.
			//void SetAsFirstSibling();	// TODO:  Move the transform to the start of the local transform list.
			//void SetAsLastSibling();	// TODO:  Move the transform to the end of the local transform list.
			//void SetPositionAndRotation();	// TODO:  Sets the world space position and rotation of the Transform component.
			//void SetSiblingIndex();	// TODO:  Sets the sibling index.
			//void TransformDirection();	// TODO:  Transforms direction from local space to world space.
			//void TransformPoint();	// TODO:  Transforms position from local space to world space.
			//void TransformVector();	// TODO:  Transforms vector from local space to world space.
			//void Translate();	// TODO:  Moves the transform in the direction and distance of translation.

		protected:

			Transform* parent;
	};

}

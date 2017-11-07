#include <string>

#include "object.h"
#include "typeinfo.h"
#include "gamedata.h"


#include <iostream>

using namespace std;

namespace ShushaoEngine {

	Object::Object() {

		name = "Object";

		GameData::RegisterObject(this);

		cout << "[" << InstanceID << "] Object Constructor" << endl;
	}

	Object::~Object() {
		Destroy(this);
	}

	string Object::ToString() {
		return name;
	}

	int Object::GetInstanceID() {
		return InstanceID;
	}

	void Object::Destroy(Object *obj, float t) {

		// TODO:
		// GameData::UnRegisterObject(this.InstanceID);

		// todo: eliminazione ritardata con t

		// delete obj;

	}

	void Object::Destroy(Object *obj) {

		// todo: eliminazione ritardata con t

		// delete obj;

	}

	/* 	TODO: Clones the object original and returns the clone.

		This function makes a copy of an object in a similar way to the Duplicate command in the editor. If you are cloning a GameObject then you can also optionally
		specify its position and rotation (these default to the original GameObject's position and rotation otherwise). If you are cloning a Component then the GameObject
		it is attached to will also be cloned, again with an optional position and rotation.

		When you clone a GameObject or Component, all child objects and components will also be cloned with their properties set like those of the original object.

		By default the parent of the new object will be null, so it will not be a "sibling" of the original. However, you can still set the parent using the overloaded
		methods. If a parent is specified and no position and rotation is specified, the position and rotation of the original will be used for the cloned object's local
		position and rotation, or its world position and rotation if the instantiateInWorldSpace parameter is true. If the position and rotation is specified, they will
		be used as the object's position and rotation in world space.

		The active status of a GameObject at the time of cloning will be passed on, so if the original is inactive then the clone will be created in an inactive state too.
	*/

	Object* Object::Instantiate(Object* original) {
		// TODO
		return nullptr;
	}

	Object* Object::Instantiate(Object* original, Transform* parent) {
		// TODO
		return nullptr;
	}

    Object* Object::Instantiate(Object* original, Transform* parent, bool instantiateInWorldSpace) {
		// TODO
		return nullptr;
    }

    Object* Object::Instantiate(Object* original, vec3 position, quat rotation) {
		// TODO
		return nullptr;
    }

    Object* Object::Instantiate(Object* original, vec3 position, quat rotation, Transform* parent) {
		// TODO
		return nullptr;
    }


}

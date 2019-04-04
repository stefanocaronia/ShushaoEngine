#pragma once

#include "component.h"
#include "entity.h"
#include "scene.h"

namespace se {

class Factory {
public:
    // static Object* Instantiate(Object*);
    // static Object* Instantiate(Object*, Transform*);
    // static Object* Instantiate(Object*, Transform*, bool);
    // static Object* Instantiate(Object*, glm::vec3, glm::quat);
    // static Object* Instantiate(Object*, glm::vec3, glm::quat, Transform*);

    template <class T, class P>
    static P* InstantiateComponent(P* originalComponent) {
        Entity* ent = originalComponent->entity;
        Entity* newEntity = ent->scene->AddEntity<T>(ent->name);
        P* newComponent = newEntity->GetComponent<P>(originalComponent->name);
        newEntity->SetActive(ent->active);
        newEntity->setParent(ent);
        return (P*)newComponent;
        return nullptr;
    }

    template <class T>
    static T* InstantiateEntity(T* originalEntity) {
        T* newEntity = ((Entity*)originalEntity)->scene->AddEntity<T>(originalEntity->name);
        newEntity->SetActive(originalEntity->active);
        newEntity->setParent(originalEntity);
        return newEntity;
    }
};

}  // namespace se

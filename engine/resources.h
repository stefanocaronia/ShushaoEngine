#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "object.h"
#include "resource.h"
#include "resources/resources.h"
#include "shaders/shader.h"
#include "texture.h"
#include "textureatlas.h"

namespace se {

class Resources {
public:
    vector<float> aci;
    static std::map<std::string, Object*> Assets;

    static std::vector<char> GetEmbeddedData(int IDRES, std::string library = "", LPCSTR type = RT_RCDATA);
    static std::string GetEmbeddedText(int IDRES, std::string library = "");

    template <class T>
    static T* Load(std::string filename, std::string name) {
        T* resource = new T(filename, name);
        auto it = Assets.find(resource->name);
        if (it != Assets.end()) {
            Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
            delete (resource);
            resource = nullptr;
            return nullptr;
        }
        Assets[name] = resource;
        return resource;
    }

    template <class T>
    static T* Load(std::string name, int IDRES, std::string library = "") {
        T* resource = new T("", name);
        bool loaded = (Resource*)resource->LoadEmbedded(IDRES, library);
        if (!loaded) {
            Debug::Log(WARNING) << "Resource " << resource->name << " not loaded" << endl;
            return nullptr;
        }
        auto it = Assets.find(resource->name);
        if (it != Assets.end()) {
            Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
            delete (resource);
            resource = nullptr;
            return nullptr;
        }
        Assets[name] = resource;
        return resource;
    }

    template <class T>
    static T* Add(std::string name) {
        T* resource = new T(name);
        auto it = Assets.find(resource->name);
        if (it != Assets.end()) {
            Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
            delete (resource);
            resource = nullptr;
            return nullptr;
        }
        Assets[name] = resource;
        return resource;
    }

    template <class T>
    static T* Add(T* asset, std::string name = "") {
        Assets[name == "" ? resource->name : name] = (T*)asset;
        auto it = Assets.find(asset->name);
        if (it != Assets.end()) {
            Debug::Log(WARNING) << "Resource " << asset->name << " already loaded" << endl;
            return nullptr;
        }
        return (T*)asset;
    }

    template <class T>
    static T* Load(std::string filename, std::string name = "") {
        T* resource = new T(filename);
        auto it = Assets.find(resource->name);
        if (it != Assets.end()) {
            Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
            delete (resource);
            resource = nullptr;
            return nullptr;
        }
        Assets[name == "" ? resource->name : name] = (T*)resource;
        return (T*)resource;
    }

    template <class T>
    static T* Get(std::string name) {
        auto it = Assets.find(name);
        if (it == Assets.end()) return nullptr;
        return (T*)Assets[name];
    }

    static void Delete(std::string name) {
        auto it = Assets.find(name);
        if (it == Assets.end()) return;
        Assets.erase(name);
        delete (Assets[name]);
    }

    static void toString();
    static void Clear();
};

}  // namespace se

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "shader.h"
#include "texture.h"
#include "textureatlas.h"

namespace se {

	class Resources {
		public:

			static std::map<std::string, Object*> Assets;

			template <class T>
			static T* Load(std::string filename, std::string name) {
				T* resource = new T(filename, name);
				auto it = Assets.find(resource->name);
				if (it != Assets.end()) {
					Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
					delete(resource);
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
					delete(resource);
					resource = nullptr;
					return nullptr;
				}
				Assets[name] = resource;
				return resource;
			}

			template <class T>
			static T* Add(T* asset) {
				Assets[asset->name] = (T*)asset;
				auto it = Assets.find(asset->name);
				if (it != Assets.end()) {
					Debug::Log(WARNING) << "Resource " << asset->name << " already loaded" << endl;
					return nullptr;
				}
				return (T*)asset;
			}

			template <class T>
			static T* Load(std::string filename) {
				T* resource = new T(filename);
				auto it = Assets.find(resource->name);
				if (it != Assets.end()) {
					Debug::Log(WARNING) << "Resource " << resource->name << " already loaded" << endl;
					delete(resource);
					resource = nullptr;
					return nullptr;
				}
				Assets[resource->name] = (T*)resource;
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
				delete(Assets[name]);
			}

			static void toString();
			static void Clear();
	};

}

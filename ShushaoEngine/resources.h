#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "shader.h"
#include "texture.h"
#include "textureatlas.h"

using namespace std;

namespace ShushaoEngine {

	class Resources {
		public:

			static map<string, Object*> Assets;

			template <class T>
			static void Load(string filename, string name) {
				T* resource = new T(filename, name);
				Assets[name] = resource;
			}

			template <class T>
			static T* Add(string name) {
				T* resource = new T(name);
				Assets[name] = resource;
				return resource;
			}

			template <class T>
			static T* Add(T* asset) {
				Assets[asset->name] = asset;
				return asset;
			}

			/*template <class T>
			static T* Add(string name, T* asset) {
				Assets[name] = asset;
				return asset;
			}*/

			template <class T>
			static T* Load(string filename) {
				T* resource = new T(filename);
				Assets[resource->name] = resource;
				return resource;
			}

			template <class T>
			static T* Get(string name) {
				auto it = Assets.find(name);
				if (it == Assets.end()) return nullptr;
				return (T*)Assets[name];
			}

			static void Delete(string name) {
				auto it = Assets.find(name);
				if (it == Assets.end()) return;
				Assets.erase(name);
				delete(Assets[name]);
			}

			static void toString();
			static void Clear();

	};

}

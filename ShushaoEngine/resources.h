#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "shader.h"
#include "texture.h"
#include "asset.h"

using namespace std;

namespace ShushaoEngine {

	class Resources {
		public:

			template <class T>
			static void Load(string filename, string name) {
				T* resource = new T(filename, name);
				Assets[name] = resource;
			}

			template <class T>
			static void Load(string filename) {
				T* resource = new T(filename);
				Assets[resource->name] = resource;
			}

			template <class T>
			static T* Get(string name) {
				return (T*)Assets[name];
			}

			static map<string, Asset*> Assets;

			static void Clean();

	};

}

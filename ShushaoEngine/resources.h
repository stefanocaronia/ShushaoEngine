#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "object.h"
#include "shader.h"
#include "texture.h"

using namespace std;

namespace ShushaoEngine {

	class Resources {
		public:

			template <class T>
			static void Load(string filename, string name) {
				T* resource = new T(filename, name);
				Assets[name] = resource;
			}

			/*template <class T>
			static T& Load(string filename) {
				T* resource = new T(filename);
				Assets[resource->name] = resource;
				return *resource;
			}

			template <class T>
			static T& Get(string name) {
				return (T&)*Assets[name];
			}*/

			template <class T>
			static T* Load(string filename) {
				T* resource = new T(filename);
				Assets[resource->name] = resource;
				return resource;
			}

			template <class T>
			static T* Get(string name) {
				return (T*)Assets[name];
			}

			static map<string, Object*> Assets;

			static void Clean();

	};

}

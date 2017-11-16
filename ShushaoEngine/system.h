#pragma once

#include <string>
#include <vector>

#include "service.h"

using namespace std;

namespace ShushaoEngine {

	class System {

		public:

			static void init();
			static void update();
			static void exit();

			static Service& Input;

			template<class T>
			static T& AddService() {
				T* service = new T();
				Services.push_back(service);
				return *service;
			}

			template<class T>
			static T& GetService() {
				for(Service* service: Services) {
					if (dynamic_cast<T*>(service))
						return dynamic_cast<T>(*service);
				}
				return nullptr;
			}

			static void Clear();

			static void ListServices();

		protected:

            static vector<Service*> Services;

		private:
	};

}

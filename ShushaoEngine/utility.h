#pragma once

#include <string>
#include <sstream>
#include <typeinfo>
#include <regex>

#define ts(str) Utility::toString(str)

using namespace std;

namespace ShushaoEngine {

	class Utility {
		public:

			static string basename(string);
			static string zerofill(int, int);

			template < typename T >
			static string toString( const T& n ) {
				ostringstream stm ;
				stm << n ;
				return stm.str() ;
			}

			template<class T>
			static string GetTitle() {
				string type = typeid(T).name();
				regex pat("N13ShushaoEngine");
				type = regex_replace(type, pat, "");

				pat = "E$";
				type = regex_replace(type, pat, "");

				string title;
				bool inName = false;
				for (char& c : type) {
					if (isdigit(c) && !inName) continue;
					if (isupper(c) && inName) title += " ";
					title += (inName?c:toupper(c));
					inName = true;
				}
				return title;
			}

	};

}

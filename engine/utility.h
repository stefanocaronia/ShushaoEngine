#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <typeinfo>
#include <regex>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define ts(str) util::toString(str)


namespace se {

	namespace util {

		std::string basename(std::string);
		std::string zerofill(int, int);

		int randomInRange(int min, int max);
		float randomInRange(float min, float max);

		template < typename T >
		std::string toString( const T& n ) {
			std::ostringstream stm ;
			stm << n ;
			return stm.str() ;
		}

		/// NB: modificare anche la versione nel cpp
		template<class T>
		std::string classtitle() {
			std::string type = typeid(T).name();
			std::regex pat("N2se|P6|P");
			type = regex_replace(type, pat, "");

			pat = "E$";
			type = regex_replace(type, pat, "");

			std::string title;
			bool inName = false;
			char prevc;
			for (char& c : type) {
				if (isdigit(c) && !inName) continue;
				if ((isupper(c) || isdigit(c)) && inName && !(c == 'D' && prevc == '2')) title += " ";
				title += (inName?c:toupper(c));
				inName = true;
				prevc = c;
			}
			return title;
		}

		std::string classtitle(std::string);
		glm::vec3 toEulerAngles(const glm::quat&);
	};

}

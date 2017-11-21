#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <typeinfo>
#include <regex>

#define ts(str) util::toString(str)

namespace ShushaoEngine {

	using namespace std;

	namespace util {

		//public:

		string basename(string);
		string zerofill(int, int);

		template < typename T >
		string toString( const T& n ) {
			ostringstream stm ;
			stm << n ;
			return stm.str() ;
		}

		template<class T>
		string classtitle() {
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

		string classtitle(string);

	};

	class vector_map : private vector<string> {

		public:
			using vector::begin;
			using vector::end;
			using vector::at;

			vector_map();
			vector_map(initializer_list<string>);
			void operator= (initializer_list<string>);
			void operator+= (string);
			void operator-= (string);
			int operator[] (string);
			string operator[] (unsigned int);
			void setDefaults(initializer_list<string>);
			void setMaxElements(unsigned int);
			int top();
			int over();
			void toString(string title = "");

		private:

			unsigned int maxElements = 32;
			vector<string> defaults = {
				"Default"
			};
	};

}

#pragma once

#include <string>
#include <sstream>

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

	};

}

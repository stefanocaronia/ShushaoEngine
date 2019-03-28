
#include <random>

#include "utility.h"
#include "globals.h"
#include "debug.h"

namespace se {

using namespace std;

namespace util {

	uint64_t timeSeed = chrono::high_resolution_clock::now().time_since_epoch().count();
    seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
	//random_device rd; // obtain a random number from hardware
	//mt19937 mt(rd()); // seed the generator
	mt19937_64 mt(ss);

	int random(int min, int max) {
		uniform_int_distribution<int> distr(min, max);
		return distr(mt);
	}

	float random(float min, float max) {
		uniform_real_distribution<float> distr(min, max);
		return distr(mt);
	}

	bool happens(float probability) {
		if (probability == 1.0f) return true;
		float tr = random(0.0f, 1.0f);
		//Debug::Log << "tr: " << tr << " probability: " << probability << endl;
		return tr <= probability;
	}

	string basename(string filename) {
		string n = filename.substr(filename.find_last_of("/\\") + 1);
		return n.substr(0, n.find_last_of("."));
	}

	string zerofill(int number, int lenght) {
		ostringstream out;
		string sNumber = toString(number);

		for (unsigned int i = 0; i < lenght - sNumber.size(); i++) {
			out << "0";
		}

		out << sNumber;

		return out.str();
	}

	/// NB: modificare anche versione template in header
	string classtitle(string type) {
		regex pat("N2se|P6|P");
		type = regex_replace(type, pat, "");

		pat = "E$";
		type = regex_replace(type, pat, "");

		string title;
		bool inName = false;
		char prevc;
		for (char& c : type) {
			if (isdigit(c) && !inName) continue;
			if ((isupper(c) || isdigit(c)) && inName && !(c == 'D' && prevc == '2')) title += " ";
			title += (inName ? c : toupper(c));
			inName = true;
			prevc = c;
		}

		return title;
	}

	glm::vec3 toEulerAngles(const glm::quat& q) {
		float roll, pitch, yaw;

		// roll (x-axis rotation)
		double sinr = 2.0f * (q.w * q.x + q.y * q.z);
		double cosr = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		roll = atan2(sinr, cosr);

		// pitch (y-axis rotation)
		double sinp = +2.0f * (q.w * q.y - q.z * q.x);
		if (fabs(sinp) >= 1)
			pitch = copysign(M_PI / 2, sinp);  // use 90 degrees if out of range
		else
			pitch = asin(sinp);

		// yaw (z-axis rotation)
		double siny = +2.0f * (q.w * q.z + q.x * q.y);
		double cosy = +1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		yaw = atan2(siny, cosy);

		return {roll, pitch, yaw};
	}

}  // namespace util

}  // namespace se

#include "utility.h"

namespace ShushaoEngine {

	namespace util {

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

		string classtitle(string type) {
			regex pat("N13ShushaoEngine|P6|P");
			type = regex_replace(type, pat, "");

			pat = "E$";
			type = regex_replace(type, pat, "");

			string title;
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

		glm::vec3 toEulerAngles(const glm::quat& q) {
			float roll, pitch, yaw;

			// roll (x-axis rotation)
			double sinr = 2.0d * (q.w * q.x + q.y * q.z);
			double cosr = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
			roll = atan2(sinr, cosr);

			// pitch (y-axis rotation)
			double sinp = +2.0f * (q.w * q.y - q.z * q.x);
			if (fabs(sinp) >= 1)
				pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
			else
				pitch = asin(sinp);

			// yaw (z-axis rotation)
			double siny = +2.0f * (q.w * q.z + q.x * q.y);
			double cosy = +1.0f - 2.0f * (q.y * q.y + q.z * q.z);
			yaw = atan2(siny, cosy);

			return {roll, pitch, yaw};
		}
	}


	//{ #region VectorMap

	VectorMap::VectorMap() {
		for (string i : defaults) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	VectorMap::VectorMap(initializer_list<string> ilist) {
		for (string i : ilist) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	void VectorMap::operator= (initializer_list<string> ilist) {
		clear();
		for (string i : defaults) {
			if (size() >= maxElements) return;
			push_back(i);
		}
		for (string i : ilist) {
			if (size() >= maxElements) return;
			push_back(i);
		}
	}

	void VectorMap::operator+= (string label) {
		if (size() >= maxElements) return;
		push_back(label);
	}

	void VectorMap::operator-= (string label) {
		erase(remove(begin(), end(), label), end());
	}

	int VectorMap::operator[] (string label) {
		auto it = find(begin(), end(), label);
		if (it != end()) {
			auto d = std::distance(begin(), it);
			return d;
		}
		return -1;
	}

	string VectorMap::operator[] (unsigned int index) {
		if (index == maxElements) return "^overall";
		if (index > (size() + 1)) return "?undefined";
		return at(index);
	}

	void VectorMap::setDefaults(initializer_list<string> ilist) {
		for (string i : ilist) defaults.push_back(i);
		for (string i : ilist) push_back(i);
	}

	int VectorMap::top() {
        return size() - 1;
	}

	int VectorMap::over() {
        return maxElements;
	}

	void VectorMap::setMaxElements(unsigned int m) {
		maxElements = m;
	}

	void VectorMap::toString(string title) {
		Logger::setColor(ConsoleColor::GREY);
		cout << " " << util::classtitle(typeid(*this).name()) << " " << title << " [" << maxElements << "] :" << endl;
		for (auto it = begin(); it != end(); ++it) {
			int key = std::distance(begin(), it);
            cout << "  (" << key << ") " << *it << endl;
		}
		// cout << "  (" << maxElements << ") " << "^overall" << endl;
		Logger::setColor(ConsoleColor::LIGHTGREY);
	}

	//}

}

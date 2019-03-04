#include <glm/glm.hpp>

#include "vao.h"
#include "debug.h"

namespace se {

	using namespace glm;
	using namespace std;

	Vao::Vao() {
		name = "Vao";
	}

	Vao::~Vao() {

		for (auto& it : buffers) {
			if (it.second != nullptr) {
				Debug::Log << "Cancello buffer" << it.second->name  << endl; //<< " (" + util::classtitle(typeid(*it.second).name()) +")"
				delete(it.second);
				it.second = nullptr;
			}
		}

		buffers.clear();

		glDeleteVertexArrays(1, &Id);
	}

	Vbo* Vao::AddBuffer(string name_, VboConfiguration config_) {
		buffers[name_] = new Vbo(config_);
		buffers[name_]->name = name_;
		return buffers[name_];
	}

	Vbo* Vao::AddBuffer(Vbo* vbo) {
		buffers[vbo->name] = vbo;
		return vbo;
	}

	Vbo* Vao::GetBuffer(std::string name) {
		auto it = buffers.find(name);
		if (it == buffers.end()) return nullptr;
		return (Vbo*)buffers[name];
	}

	Vao* Vao::Use() {
		if (!Id) {
			Debug::Log(ERROR) << "VAO not initializated" << endl;
		}
		glBindVertexArray(Id);
		inUse = true;
		return this;
	}

	Vao* Vao::Leave() {
		glBindVertexArray(0);
		inUse = false;
		return this;
	}

	Vao* Vao::Init() {
		if (ready) return this;
		glGenVertexArrays(1, &Id);

		Use();
		for (auto& it : buffers) {
			if (it.second != nullptr && !it.second->ready) {
				(Vbo*)it.second->Init();
			}
		}
		Leave();

		ready = (Id > 0);
		return this;
	}
}

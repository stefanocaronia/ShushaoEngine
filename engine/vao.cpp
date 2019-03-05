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
		Vbo* buff = new Vbo(config_);
		buff->name = name_;
		AddBuffer(buff);
		return buffers[name_];
	}

	Vbo* Vao::AddBuffer(Vbo* vbo_) {
		buffers[vbo_->name] = vbo_;
		return vbo_;
	}

	Vbo* Vao::GetBuffer(std::string name_) {
		auto it = buffers.find(name_);
		if (it == buffers.end()) return nullptr;
		return (Vbo*)buffers[name_];
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

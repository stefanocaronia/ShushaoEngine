#pragma once

#include <glm/glm.hpp>

#include <glew.h>
#include "renderer.h"
#include "color.h"
#include "material.h"
#include "mesh.h"

namespace se {

	class Shader;

	class MeshRenderer : public Renderer {

		public:

			MeshRenderer();
			~MeshRenderer();
			MeshRenderer(std::string);

			bool isReady();

			Vao* VAO = nullptr;
			Mesh* mesh = nullptr;
			Material* material = nullptr;

			MeshRenderer* SetMesh(Mesh* mesh_) {
				mesh = mesh_;
				return this;
			}

			MeshRenderer* SetMaterial(Material* material_) {
				material = material_;
				return this;
			}

		protected:

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

		private:
	};

}

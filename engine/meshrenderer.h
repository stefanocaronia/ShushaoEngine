#pragma once

#include <glm/glm.hpp>

#include <glew.h>
#include "renderer.h"
#include "color.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"

namespace se {

	class MeshRenderer : public Renderer {

		public:

			MeshRenderer();
			~MeshRenderer();
			MeshRenderer(std::string);

			bool isReady();

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

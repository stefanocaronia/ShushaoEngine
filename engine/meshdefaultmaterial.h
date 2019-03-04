#pragma once

#include "material.h"

namespace se {

	class MeshDefaultMaterial : public Material {

		public:
			MeshDefaultMaterial();

			Texture* diffuse = nullptr;
			Texture* normal = nullptr;
			Texture* bump = nullptr;
			Texture* specular = nullptr;

		protected:

			void Init();

		private:
	};

}

#pragma once

#include "shader.h"

namespace se {

	class PhongShader : public Shader {

		public:
			PhongShader();

		protected:

			void Awake();
			void Update();
	};

}


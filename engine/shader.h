#pragma once

#include <string>
#include <GL/glew.h>

#include "object.h"

namespace se {

	enum ShaderLocation {
		POSITION = 0,
		TEXCOORD = 1,
		COLOR = 2
	};

	class Shader : public Object {

		public:

			Shader();
			Shader(std::string);
			Shader(std::string, std::string);

			~Shader();

			bool Init();

			bool Load(std::string);

			GLuint GetProgram();

			void LoadFromString(std::string vsc, std::string fsc);

		protected:
		private:

			GLuint programID = 0;

			bool debug = false;

			GLuint VertexShaderID;
			GLuint FragmentShaderID;

			std::string VertexShaderCode;
			std::string FragmentShaderCode;

			bool loadWithName(std::string, std::string);

			bool compile();
			bool link();

			bool shaderCompilationLog(const GLuint&);
			bool programCompilationLog(const GLuint&);
	};

}

#pragma once

#include <string>
#include <GL/glew.h>

#include "object.h"

namespace ShushaoEngine {

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

			bool Init();

			bool loadWithName(std::string, std::string);

			~Shader();

			bool Load(std::string);

			GLuint getProgram();
			GLuint programID = 0;

			std::string VertexShaderCode;
			std::string FragmentShaderCode;

		protected:
		private:

			GLuint VertexShaderID;
			GLuint FragmentShaderID;

			bool debug = false;

			bool compile();
			bool link();

			bool shaderCompilationLog(const GLuint&);
			bool programCompilationLog(const GLuint&);
	};

}

#pragma once

#include <string>
#include "object.h"

#include "libs.h"

namespace ShushaoEngine {

	enum ShaderLocation {
		POSITION = 0,
		TEXCOORD = 1
	};

	class Shader : public Object {

		public:

			Shader();
			Shader(string);
			Shader(string, string);

			~Shader();

			bool Load(string);

			GLuint getProgram();
			GLuint getLastProgram();
			GLuint programID = 0;

			string VertexShaderCode;
			string FragmentShaderCode;

		protected:
		private:

			GLuint VertexShaderID;
			GLuint FragmentShaderID;

			bool debug = true;

			bool compile();
			bool link();

			bool shaderCompilationLog(const GLuint&);
			bool programCompilationLog(const GLuint&);
	};

}

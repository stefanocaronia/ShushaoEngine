#pragma once

#include <string>

#include "libs.h"

using namespace std;

namespace ShushaoEngine {

	class ShaderProgram {

		public:
			ShaderProgram();
			ShaderProgram(string);
			~ShaderProgram();

			bool load(string);

			GLuint getProgram();
			GLuint getLastProgram();
			GLuint programID = 0;

			string VertexShaderCode;
			string FragmentShaderCode;

		protected:

			string shadersPath = "shaders/";

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

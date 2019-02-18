#pragma once

#include <string>
#include <map>
#include <glew.h>

#include "object.h"
#include "color.h"

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

			virtual void awake();
			virtual void render();
			virtual void exit();

			GLuint GetProgram();

			void LoadFromString(std::string vsc, std::string fsc);

			Color color = {1.0f, 1.0f, 1.0f, 1.0f};
			GLint texture = GL_TEXTURE0;
			const GLfloat* mvp;

			// attributes
			GLint aPosition;
			GLint aTextureCoord;
			GLint aColor;

			// uniforms
			GLint uMvp;
			GLint uTextureId;
			GLint uColor;

		protected:

			virtual void Awake();
			virtual void Render();
			virtual void Exit();

		private:

			GLuint programID = 0;

			bool debug = true;

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

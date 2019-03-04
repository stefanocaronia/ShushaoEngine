#pragma once

#include <string>
#include <map>
#include <glew.h>

#include "object.h"
#include "color.h"

namespace se {

	enum class UniformType {
		FLOAT,
		INTEGER,
		MATRIX,
		VECTOR,
		TEXTURE,
		COLOR
	};

	enum ShaderLocation {
		LOCATION_POSITION = 1,
		LOCATION_TEXCOORD = 2,
		LOCATION_COLOR = 3,
		LOCATION_NORMAL = 4,
		LOCATION_MVP = 5,
		LOCATION_RENDER_COLOR = 6,
		LOCATION_MAIN_TEXTURE = 7,
		LOCATION_FONTCOORD = 8
	};

	class Uniform {

		public:

			Uniform(std::string name_,
				std::string var_,
				UniformType type_,
				GLuint location_,
				bool locked_ = false) : name(name_), var(var_), type(type_), location(location_), locked(locked_) {}

			std::string name;
			std::string var;
			UniformType type;
			GLuint location = 0;
			bool locked = false;

			// values
			GLenum texture;

			void SetFloat(GLfloat&);
			void SetInteger(GLint&);
			void SetTexture(GLenum&);
			void SetMatrix(GLfloat*);
			void SetVector(glm::vec4&);
			void SetColor(Color&);
	};

	class Shader : public Object {

		public:

			std::map<std::string, Uniform> uniforms;

			Shader();
			Shader(std::string);
			Shader(std::string, std::string);
			~Shader();

			bool Init();
			bool Load(std::string);
			void LoadFromString(std::string vsc, std::string fsc);

			void awake();
			void update();
			void exit();

			bool inUse = false;

			void Use() {
				if (!programID) return;
				glUseProgram(programID);
				inUse = true;
			}

			void Leave() {
				if (!programID) return;
				glUseProgram(0);
				inUse = false;
			}

			GLuint GetProgram();

            void AddUniform(std::string name_, std::string var_, UniformType type_, GLuint location_ = 0, bool locked_ = false);
            void AddUniform(std::string var_, UniformType type_, GLuint location_ = 0, bool locked_ = false);

            void SetFloat(std::string, GLfloat);
			void SetInteger(std::string, GLint);
			void SetTexture(std::string, GLenum);
			void SetMatrix(std::string, GLfloat*);
			void SetVector(std::string, glm::vec4);
			void SetColor(std::string, Color);

			GLenum GetTexture(std::string);

			void SetMVP(GLfloat*);
			void SetRenderColor(Color);

		protected:

			// per override
			virtual void Awake();
			virtual void Update();
			virtual void Exit();

			std::string VertexShaderCode;
			std::string FragmentShaderCode;
			std::string GeometryShaderCode;

		private:

			GLuint programID = 0;

			bool debug = true;

			GLuint VertexShaderID;
			GLuint FragmentShaderID;


			bool loadWithName(std::string, std::string);

			bool compile();
			bool link();

			bool shaderCompilationLog(const GLuint&);
			bool programCompilationLog(const GLuint&);

	};

}

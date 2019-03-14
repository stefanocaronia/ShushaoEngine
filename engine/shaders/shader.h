#pragma once

#include <string>
#include <map>
#include <GL/glew.h>

#include "object.h"
#include "color.h"
#include "light.h"

namespace se {

	enum class UniformType {
		FLOAT,
		INTEGER,
		MATRIX,
		VECTOR,
		TEXTURE,
		COLOR,
		LIGHT
	};

	enum ShaderLocation {
		LOCATION_POSITION = 1,
		LOCATION_TEXCOORD = 2,
		LOCATION_COLOR = 3,
		LOCATION_NORMAL = 4,
		LOCATION_MVP = 5,
		LOCATION_RENDER_COLOR = 6
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
			void SetTextureIndex(GLint&);
			void SetMatrix(GLfloat*);
			void SetVector(glm::vec2&);
			void SetVector(glm::vec3&);
			void SetVector(glm::vec4&);
			void SetColor(Color&);
			void SetLight(UniformLight&);
	};

	class Shader : public Object {

		public:

			std::map<std::string, Uniform> uniforms;

			Shader();
			Shader(std::string);
			Shader(std::string, std::string);
			~Shader();

			bool inUse = false;

			bool Init();
			void Use();
			void Leave();
			bool Load(std::string);
			void LoadFromString(std::string vsc, std::string fsc);

			void awake();
			void update();
			void exit();

			GLuint GetProgram();

            void AddUniform(std::string name_, std::string var_, UniformType type_, GLuint location_ = 0);
            void AddUniform(std::string var_, UniformType type_, GLuint location_ = 0);
			void AddShaderUniform(std::string var_, UniformType type_, GLuint location_ = 0);
			void AddShaderUniform(std::string name_, std::string var_, UniformType type_, GLuint location_ = 0);

            void SetFloat(std::string, GLfloat);
			void SetInteger(std::string, GLint);
			void SetTextureIndex(std::string, GLint);
			void SetMatrix(std::string, GLfloat*);
			void SetVector(std::string, glm::vec2);
			void SetVector(std::string, glm::vec3);
			void SetVector(std::string, glm::vec4);
			void SetColor(std::string, Color);
			void SetLight(string, UniformLight&);

			GLenum GetTextureIndex(std::string);

			void SetMVP(GLfloat*);
			void SetM(GLfloat*);
			void SetRenderColor(Color);

			void Enable(std::string var);
			void Disable(std::string var);

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
			GLuint GeometryShaderID;

			bool loadWithName(std::string, std::string);

			bool compile();
			bool link();

			bool shaderCompilationLog(const GLuint&);
			bool programCompilationLog(const GLuint&);

	};

}

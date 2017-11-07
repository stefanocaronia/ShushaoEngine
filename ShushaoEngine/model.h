#pragma once
#include "libs.h"
#include "texture.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class Model
	{
		public:

			Model();

			bool setVertexData(const GLfloat*,int);
			bool setVertexData(std::vector<glm::vec3>);
			bool setUvData(const GLfloat*,int);
			bool setUvData(std::vector<glm::vec2>);
			bool setColorData(GLfloat*);
			bool setColorData(std::vector<glm::vec3>);
			bool setNormalData(GLfloat*);
			bool setNormalData(std::vector<glm::vec3>);

			Texture* texture;

			bool loadTexture(string );
			bool loadObject(string);

			GLuint textureID;
			vector<vec3> vertexData;
			vector<vec2> uvData;
			vector<vec4> colorData;
			vector<vec3> normalsData;

			GLuint vertexBuffer;
			GLuint uvBuffer;

			GLuint VAO;
			SDL_Surface* Surface;
			bool init();

	};

}

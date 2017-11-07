#include "sprite.h"
#include "rect.h"


namespace ShushaoEngine {

	Sprite::Sprite() {
        cout << "[" << InstanceID << "] Sprite Constructor" << endl;
        name = "Sprite";
	}

	Sprite::Sprite(Texture* _texture) {
		texture = _texture;
        rect.Set(0.0f, 0.0f, (float)texture->width, (float)texture->height);
        pivot = rect.center;
        updateVertices();
	}

	Sprite::Sprite(Texture* _texture, Rect _rect, vec2 _offset) {
		texture = _texture;
        rect = _rect;
		textureRectOffset = _offset;
		pivot = rect.center;
		updateVertices();
	}

	void Sprite::updateVertices() {

		GLfloat wX = (rect.width / pixelPerUnit) / 2;
		GLfloat wY = (rect.height / pixelPerUnit) / 2;

		GLfloat v[] = {
			-wX,  wY, 0.0f, // Top-left
			 wX, -wY, 0.0f, // Top-right
			 wX, -wY, 0.0f, // Bottom-righ
			-wX, -wY, 0.0f // Bottom-left
		};

		for (unsigned int i = 0; i < 12;  i++) {
            vertices[i] = v[i];
		}

	}

	Sprite::~Sprite() {
		//dtor
	}

	vector<vec3> Sprite::getVertices() {
		vector<vec3> vectorVertices;
		for (unsigned int i=0; i<=(sizeof(vertices)/sizeof(GLfloat)); i+=3) {
			if (i>0) vectorVertices.push_back(vec3(vertices[i-3], vertices[i-2], vertices[i-1]));
		}
		return vectorVertices;
	}

	vector<vec2> Sprite::getUV() {
		vector<vec2> vectorUV;
		for (unsigned int i=0; i<=(sizeof(uv)/sizeof(GLfloat)); i+=2) {
			if (i>0) vectorUV.push_back(vec2(uv[i-2],uv[i-1]));
		}
		return vectorUV;
	}

	void Sprite::initVAO() {

		if (VAO > 0) return;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), &indexes, GL_STATIC_DRAW);

		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv), &uv, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

}

#include  <iostream>
#include <string>

#include "resources.h"
#include "sprite.h"
#include "rect.h"

using namespace std;

namespace ShushaoEngine {

	Sprite::Sprite() {
        name = "Sprite";
	}

	Sprite::~Sprite() {
		if (texture != nullptr) delete(texture);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteBuffers(1, &uvBuffer);
	}

	Sprite::Sprite(string n) {
        name = n;
	}

	Sprite::Sprite(string n, Texture* _texture) {
		name = n;
		rect.Set(0.0f, 0.0f, (float)_texture->width, (float)_texture->height);
		pixel_pivot = calculatePivot(PivotPosition::CENTER, rect);
		setTexture(_texture);
	}

	Sprite::Sprite(string n, Texture* _texture, Rect _rect, PivotPosition _pivotPosition, vec2 _offset) {
		name = n;
        rect = _rect;
		pixel_pivot = calculatePivot(_pivotPosition, _rect);
		textureRectOffset = _offset;
		setTexture(_texture);
	}

	Sprite* Sprite::setRect(Rect _rect) {
        rect = _rect;
        pixel_pivot = calculatePivot(PivotPosition::CENTER, _rect);
		init();
		return this;
	}

	Sprite* Sprite::setPixelPerUnit(float ppu) {
        pixelPerUnit = ppu;
		init();
		return this;
	}

	Sprite* Sprite::setPivot(vec2 _pivot) {
        pixel_pivot = calculatePivot(PivotPosition::CUSTOM, rect, _pivot);
		init();
		return this;
	}

	Sprite* Sprite::setTexture(Texture* tex) {
        texture = tex;
		init();
		return this;
	}

	Rect Sprite::getRect() {
       return rect;
	}

	vec2 Sprite::getPivot() {
        return pivot;
	}

	Sprite* Sprite::init() {

		GLfloat wX = (rect.width / pixelPerUnit) / 2;
		GLfloat wY = (rect.height / pixelPerUnit) / 2;

		pivot.x = (pixel_pivot.x - (rect.width / 2)) / (float)pixelPerUnit;
		pivot.y = -(pixel_pivot.y - (rect.height / 2)) / (float)pixelPerUnit;

		GLfloat v[] = {
			-wX, -wY, 0.0f, // Bottom-left
			 wX, -wY, 0.0f, // Bottom-right
			 wX,  wY, 0.0f, // Top-right
			-wX,  wY, 0.0f // Top-left
		};

		for (unsigned int i = 0; i < 12;  i++) {
            vertices[i] = v[i];
		}

		if (rect.width < texture->width || rect.height < texture->height) {

			// rect in texture coord
			Rect tsr(
				rect.x / texture->width,
				rect.y / texture->height,
				rect.width / texture->width,
				rect.height / texture->height
			);

			GLclampd u[8] = { // The base texture coordinates of the sprite mesh.
				tsr.x, tsr.yMax, // Bottom-left of texture
				tsr.xMax, tsr.yMax, // Bottom-right of texture
				tsr.xMax, tsr.y, // Top-Right of texture
				tsr.x, tsr.y // Top-left of texture
			};

			for (unsigned int i = 0; i < 8;  i++) {
				uv[i] = u[i];
			}
		}

		initVAO();

		return this;
	}

	Sprite* Sprite::initVAO() {

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

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(ShaderLocation::POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::POSITION);

		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(ShaderLocation::TEXCOORD, 2, GL_DOUBLE, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ShaderLocation::TEXCOORD);

		glBindVertexArray(0);

		return this;
	}

	vec2 Sprite::calculatePivot(PivotPosition pp, Rect re, vec2 custom) {
		vec2 piv;
		switch (pp) {
			case (PivotPosition::CENTER): piv= re.center; break;
			case (PivotPosition::TOPLEFT): piv = re.topleft; break;
			case (PivotPosition::TOPRIGHT): piv = re.topright; break;
			case (PivotPosition::TOP): piv = re.top; break;
			case (PivotPosition::LEFT): piv = re.left; break;
			case (PivotPosition::RIGHT): piv = re.right; break;
			case (PivotPosition::BOTTOMLEFT): piv = re.bottomleft; break;
			case (PivotPosition::BOTTOMRIGHT): piv = re.bottomright; break;
			case (PivotPosition::BOTTOM): piv = re.bottom; break;
			case (PivotPosition::CUSTOM): return custom; break;
		}

		return piv - re.position;
	}

	/*vector<vec3> Sprite::getVertices() {
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
	}*/

}

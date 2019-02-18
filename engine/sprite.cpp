#include  <iostream>
#include <string>

#include "shader.h"
#include "debug.h"
#include "sprite.h"
#include "rect.h"
#include "types.h"

using namespace std;

namespace se {

	Sprite::Sprite() {
        name = "Sprite";
	}

	Sprite::~Sprite() {
	}

	Sprite::Sprite(string n) {
        name = n;
	}

	Sprite::Sprite(string n, Texture* _texture) {
		name = n;
		rect.Set(0.0f, 0.0f, (float)_texture->width, (float)_texture->height);
		pixel_pivot = CalculatePivot(PivotPosition::CENTER, rect);
		texture = _texture;
		init();
	}

	Sprite::Sprite(string n, Texture* _texture, Rect _rect, PivotPosition _pivotPosition, vec2 _offset) {
		name = n;
        rect = _rect;
		pixel_pivot = CalculatePivot(_pivotPosition, _rect);
		textureRectOffset = _offset;
		texture = _texture;
		init();
	}

	Sprite* Sprite::SetRect(Rect _rect) {
        rect = _rect;
        pixel_pivot = CalculatePivot(PivotPosition::CENTER, _rect);
		init();
		return this;
	}

	Sprite* Sprite::SetPixelPerUnit(float ppu) {
        pixelPerUnit = ppu;
		init();
		return this;
	}

	Sprite* Sprite::SetPivot(vec2 _pivot) {
        pixel_pivot = CalculatePivot(PivotPosition::CUSTOM, rect, _pivot);
		init();
		return this;
	}

	Sprite* Sprite::SetPivot(PivotPosition _pivotPosition) {
        pixel_pivot = CalculatePivot(_pivotPosition, rect);
		init();
		return this;
	}

	Sprite* Sprite::SetTexture(Texture* texture_) {
        texture = texture_;
        rect.Set(0.0f, 0.0f, (float)texture_->width, (float)texture_->height);
		pixel_pivot = CalculatePivot(PivotPosition::CENTER, rect);
		init();
		return this;
	}

	Rect Sprite::GetRect() {
       return rect;
	}

	vec2 Sprite::GetPivot() {
        return pivot;
	}

	Sprite* Sprite::init() {

		uv = { // The base texture coordinates of the sprite mesh.
			{ 0.0f, 1.0f }, // Bottom-left of texture
			{ 1.0f, 1.0f }, // Bottom-right of texture
			{ 1.0f, 0.0f }, // Top-Right of texture
			{ 0.0f, 0.0f } // Top-left of texture
		};

		indexes = {
			0, 1, 2,
			2, 3, 0
		};

		VAO.SetUv(uv);
		VAO.SetIndexes(indexes);

		pivot.x = (pixel_pivot.x - (rect.width / 2)) / (float)pixelPerUnit;
		pivot.y = -(pixel_pivot.y - (rect.height / 2)) / (float)pixelPerUnit;

		GLfloat wX = ((rect.width / pixelPerUnit) / 2);
		GLfloat wY = ((rect.height / pixelPerUnit) / 2);

		vertices = {
			{-wX - pivot.x, -wY - pivot.y, 0.0f}, // Bottom-left
			{ wX - pivot.x, -wY - pivot.y, 0.0f}, // Bottom-right
			{ wX - pivot.x,  wY - pivot.y, 0.0f}, // Top-right
			{-wX - pivot.x,  wY - pivot.y, 0.0f} // Top-left
		};

		VAO.SetVertices(vertices);

		// memcpy(vertices, v, sizeof(GLfloat) * 12);

		if (rect.width < texture->width || rect.height < texture->height) {

			// rect in texture coord
			Rect tsr(
				rect.x / texture->width,
				rect.y / texture->height,
				rect.width / texture->width,
				rect.height / texture->height
			);

			uv = { // The base texture coordinates of the sprite mesh.
				{ tsr.x, tsr.yMax}, // Bottom-left of texture
				{ tsr.xMax, tsr.yMax}, // Bottom-right of texture
				{ tsr.xMax, tsr.y}, // Top-Right of texture
				{ tsr.x, tsr.y} // Top-left of texture
			};

			VAO.SetUv(uv);

			// memcpy(uv, u, sizeof(GLclampd) * 8);
		}

		return this;
	}

	/*Sprite* Sprite::initVAO() {

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

		VAOInitialized = true;

		return this;
	}*/

	vec2 Sprite::CalculatePivot(PivotPosition pp, Rect re, vec2 custom) {
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
}

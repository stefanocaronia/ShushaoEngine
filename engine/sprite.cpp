#include <iostream>
#include <string>

#include "shader.h"
#include "debug.h"
#include "sprite.h"
#include "rect.h"
#include "types.h"

namespace se {

	using namespace std;
	using namespace glm;

	Sprite::Sprite() {
        name = "Sprite";
		Init();
	}

	Sprite::Sprite(string n) {
        name = n;
		Init();
	}

	Sprite::Sprite(string n, Texture* texture_) {
		name = n;
		SetTexture(texture_);
		Init();
	}

	Sprite::~Sprite() {
		delete(VAO);
		VAO = nullptr;
	}

	Sprite* Sprite::Init() {
		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
		VAO->AddBuffer(Vbo::UV, VBO_CONFIG_UV);
		VAO->AddBuffer(Vbo::NORMALS, VBO_CONFIG_NORMAL);
		VAO->AddBuffer(Vbo::INDEXES, VBO_CONFIG_INDEX);
		VAO->Init();
		return this;
	}

	Sprite* Sprite::SetRect(Rect rect_) {
        rect = rect_;
        pixel_pivot = CalculatePivot(Align::CENTER, rect_);
		return this;
	}

	Sprite* Sprite::SetPixelPerUnit(unsigned int ppu) {
        pixelPerUnit = ppu;
		return this;
	}

	Sprite* Sprite::SetPivot(vec2 _pivot) {
        pixel_pivot = CalculatePivot(Align::CUSTOM, rect, _pivot);
		return this;
	}

	Sprite* Sprite::SetPivot(Align pivotpos_) {
        pixel_pivot = CalculatePivot(pivotpos_, rect);
		return this;
	}

	Sprite* Sprite::SetTexture(Texture* texture_) {
        texture = texture_;
        rect.Set(0.0f, 0.0f, (float)texture_->width, (float)texture_->height);
		pixel_pivot = CalculatePivot(Align::CENTER, rect);
		return this;
	}

	Rect Sprite::GetRect() {
       return rect;
	}

	vec2 Sprite::GetPivot() {
        return pivot;
	}

	Sprite* Sprite::Build() {

		pivot.x = (pixel_pivot.x - (rect.width / 2)) / (GLfloat)pixelPerUnit;
		pivot.y = -(pixel_pivot.y - (rect.height / 2)) / (GLfloat)pixelPerUnit;

		GLfloat wX = ((rect.width / pixelPerUnit) / 2);
		GLfloat wY = ((rect.height / pixelPerUnit) / 2);

		vertices.clear();
		vertices = {
			{-wX - pivot.x, -wY - pivot.y, 0.0f}, // Bottom-left
			{ wX - pivot.x, -wY - pivot.y, 0.0f}, // Bottom-right
			{ wX - pivot.x,  wY - pivot.y, 0.0f}, // Top-right
			{-wX - pivot.x,  wY - pivot.y, 0.0f} // Top-left
		};

		if (rect.width < texture->width || rect.height < texture->height) {

			// rect in texture coord
			Rect tsr(
				rect.x / texture->width,
				rect.y / texture->height,
				rect.width / texture->width,
				rect.height / texture->height
			);

			uv = { // The base texture coordinates of the sprite mesh.
				{tsr.x, tsr.yMax}, // Bottom-left of texture
				{tsr.xMax, tsr.yMax}, // Bottom-right of texture
				{tsr.xMax, tsr.y}, // Top-Right of texture
				{tsr.x, tsr.y} // Top-left of texture
			};
		}

		VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertices);
		VAO->Load<vec2>(Vbo::UV, uv);
		VAO->Load<vec3>(Vbo::NORMALS, normals);
		VAO->Load<GLushort>(Vbo::INDEXES, indexes);
		VAO->Leave();

		ready = true;
		return this;
	}

	vec2 Sprite::CalculatePivot(Align pp, Rect re, vec2 custom) {
		vec2 piv;
		switch (pp) {
			case (Align::CENTER): piv= re.center; break;
			case (Align::TOPLEFT): piv = re.topleft; break;
			case (Align::TOPRIGHT): piv = re.topright; break;
			case (Align::TOP): piv = re.top; break;
			case (Align::LEFT): piv = re.left; break;
			case (Align::RIGHT): piv = re.right; break;
			case (Align::BOTTOMLEFT): piv = re.bottomleft; break;
			case (Align::BOTTOMRIGHT): piv = re.bottomright; break;
			case (Align::BOTTOM): piv = re.bottom; break;
			case (Align::CUSTOM): return custom; break;
		}

		return piv - re.position;
	}
} // namespace se

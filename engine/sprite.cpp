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

	Sprite::~Sprite() {
		delete(VAO);
		VAO = nullptr;
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

	Sprite* Sprite::SetRect(Rect rect_) {
        rect = rect_;
        pixel_pivot = CalculatePivot(PivotPosition::CENTER, rect_);
		return this;
	}

	Sprite* Sprite::SetPixelPerUnit(unsigned int ppu) {
        pixelPerUnit = ppu;
		return this;
	}

	Sprite* Sprite::SetPivot(vec2 _pivot) {
        pixel_pivot = CalculatePivot(PivotPosition::CUSTOM, rect, _pivot);
		return this;
	}

	Sprite* Sprite::SetPivot(PivotPosition pivotpos_) {
        pixel_pivot = CalculatePivot(pivotpos_, rect);
		return this;
	}

	Sprite* Sprite::SetTexture(Texture* texture_) {
        texture = texture_;
        rect.Set(0.0f, 0.0f, (float)texture_->width, (float)texture_->height);
		pixel_pivot = CalculatePivot(PivotPosition::CENTER, rect);
		return this;
	}

	Rect Sprite::GetRect() {
       return rect;
	}

	vec2 Sprite::GetPivot() {
        return pivot;
	}

	Sprite* Sprite::Init() {

		VAO = new Vao();
		VAO->AddBuffer("vertex", VBO_CONFIG_VERTEX);
		VAO->AddBuffer("uv", VBO_CONFIG_UV);
		VAO->AddBuffer("index", VBO_CONFIG_INDEX);
		VAO->Init();

		return this;
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
				tsr.x, tsr.yMax, // Bottom-left of texture
				tsr.xMax, tsr.yMax, // Bottom-right of texture
				tsr.xMax, tsr.y, // Top-Right of texture
				tsr.x, tsr.y // Top-left of texture
			};
		}

		VAO->Use();
		VAO->Load<vec3>("vertex", vertices);
		VAO->Load<GLclampd>("uv", uv);
		VAO->Load<GLushort>("index", indexes);
		VAO->Leave();

		ready = true;

		return this;
	}

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

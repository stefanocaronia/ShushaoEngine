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
		delete(VAO);
		VAO = nullptr;
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

		VAO = new Vao(GL_STATIC_DRAW);

		pivot.x = (pixel_pivot.x - (rect.width / 2)) / (float)pixelPerUnit;
		pivot.y = -(pixel_pivot.y - (rect.height / 2)) / (float)pixelPerUnit;

		float wX = ((rect.width / pixelPerUnit) / 2);
		float wY = ((rect.height / pixelPerUnit) / 2);

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

			// memcpy(uv, u, sizeof(GLclampd) * 8);
		}

		VAO->SetUv(uv);
		VAO->SetVertices(vertices);
		VAO->SetIndexes(indexes);

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

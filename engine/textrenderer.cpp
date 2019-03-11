#include <iostream>

#include "textrenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"
#include "fontshader.h"
#include "design.h"

namespace se {

    using namespace std;
    using namespace glm;

	TextRenderer::TextRenderer() {
		name = "Font Renderer";
		shader = GLManager::GetShader<FontShader>();

		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_FONT);
	}

	TextRenderer::~TextRenderer() {

	}

	TextRenderer::TextRenderer(string name_) {
		name = name_;
	}

	bool TextRenderer::isReady() {
		return (font != nullptr && shader != nullptr && transform != nullptr);
	}

	void TextRenderer::Awake() {
		shader->awake();
		VAO->Init();
	}

	void TextRenderer::Update() {}

	void TextRenderer::write(string text_) {

		vec2 offset_  = offset * (float)pixelPerUnit;
		vec2 pos = offset_;

		Rect alignedRect = rect;

		switch (pivot) {
			case Align::TOPLEFT:
				alignedRect.SetY(-rect.height);
				pos += alignedRect.topleft;
				break;
			case Align::TOPRIGHT:
				alignedRect.SetPosition({-rect.width, -rect.height});
				break;
			case Align::BOTTOMRIGHT:
				alignedRect.SetX(-rect.width);
				break;
			case Align::LEFT:
				alignedRect.SetY(-rect.center.y);
				break;
			case Align::RIGHT:
				alignedRect.SetPosition({-rect.width, -rect.center.y});
				break;
			case Align::TOP:
				alignedRect.SetPosition({-rect.center.x, -rect.height});
				break;
			case Align::BOTTOM:
				alignedRect.SetX(-rect.center.x);
				break;
			case Align::CENTER:
				alignedRect.SetPosition({-rect.center.x, -rect.center.y});
				break;
			case Align::BOTTOMLEFT:
			case Align::CUSTOM:
				break;
		}

		if (Debug::enabled) {
			Design::DrawRect(transform->position, alignedRect, {0.1, 0.5, 0.1, 0.4});
		}

		const char *p;
		FT_GlyphSlot g = font->face->glyph;

		GLuint tex;
		glGenTextures(1, &tex);
		glActiveTexture(shader->GetTextureIndex("diffuse_map"));
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		float width = 0;
		float height = 0;

		vec2 lpos;

		for (p = text_.c_str(); *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			width += (((g->advance.x) / 64) * scale.x) / Config::pixelPerUnit;
			float thisHeight = (g->bitmap.rows * scale.y) / Config::pixelPerUnit;
			float thisBearing = (g->bitmap_top * scale.y) / Config::pixelPerUnit;
			height = std::max(height, (g->bitmap.rows * scale.y) / Config::pixelPerUnit);
		}

		Rect textBox {0, 0, width, height};

		pos += (alignedRect.topleft * (float)Config::pixelPerUnit);

		switch (align) {// si parte da bottomleft
			case Align::TOPLEFT:
				pos.y += (alignedRect.height - textBox.height) * (float)Config::pixelPerUnit;
				break;
			case Align::TOPRIGHT:
				pos.y += (alignedRect.height - textBox.height) * (float)Config::pixelPerUnit;
				pos.x += (alignedRect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::BOTTOMLEFT:
				// rimane uguale
				break;
			case Align::BOTTOMRIGHT:
				pos.x += (alignedRect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::LEFT:
				pos.y += ((alignedRect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::RIGHT:
				pos.y += ((alignedRect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				pos.x += (alignedRect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::TOP:
				pos.x += ((alignedRect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				pos.y += (alignedRect.height - textBox.height) * (float)Config::pixelPerUnit;
				break;
			case Align::BOTTOM:
				pos.x += ((alignedRect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::CENTER:
				pos.x += ((alignedRect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				pos.y += ((alignedRect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::CUSTOM:
			default:
				pos.y += (alignedRect.height - textBox.height) * (float)Config::pixelPerUnit;

		}

		for (p = text_.c_str(); *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			float x2 = (pos.x + g->bitmap_left * scale.x) / Config::pixelPerUnit;
			float y2 = (-pos.y - g->bitmap_top * scale.y) / Config::pixelPerUnit;
			float w = (g->bitmap.width * scale.x) / Config::pixelPerUnit;
			float h = (g->bitmap.rows * scale.y) / Config::pixelPerUnit;

			vector<vec4> box {
				{ x2,     -y2, 		0, 0 },
				{ x2 + w, -y2, 		1, 0 },
				{ x2,     -y2 - h, 	0, 1 },
				{ x2 + w, -y2 - h, 	1, 1 }
			};

			VAO->Load<vec4>(Vbo::VERTICES, box);
			glBindBuffer(GL_ARRAY_BUFFER, VAO->GetBuffer(Vbo::VERTICES)->Id);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			pos.x += ((g->advance.x) / 64) * scale.x;
			pos.y += ((g->advance.y) / 64) * scale.y;
		}

		glDeleteTextures(1, &tex);
	}

    void TextRenderer::Render() {

		if (!isReady()) return;

		shader->Use();
		shader->SetMVP(transform->uMVP());
		shader->SetRenderColor(color);
		shader->update();

		VAO->Use();

		write(text);

		VAO->Leave();
		shader->Leave();
	}

	void TextRenderer::OnDestroy() {

	}

}

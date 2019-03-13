#include <iostream>

#include "text.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"
#include "fontshader.h"
#include "design.h"
#include "entity.h"

namespace se {

    using namespace std;
    using namespace glm;

	void Text::setup() {
		entity->transform->isRectTransform = true;
		shader = new FontShader();
		VAO = new Vao();
		VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_FONT);
	}

	bool Text::isReady() {
		return (font != nullptr && shader != nullptr && transform != nullptr);
	}

	void Text::Awake() {
		shader->awake();
		VAO->Init();

		if (entity->canvas != nullptr && entity->canvas->renderMode == RenderMode::SCREEN) {
			shader->Use();
			shader->SetVector("viewport", GLManager::VIEWPORT);
			shader->Enable("viewport");
			shader->Leave();
		}
	}

	void Text::Update() {}

	void Text::write(string text_) {

		vec2 offset_  = offset * (float)pixelPerUnit;
		vec2 pos = offset_;

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
		unsigned int pixelHeight = 0;
		unsigned int baselineGap = 0;

		vec2 lpos;

		for (p = text_.c_str(); *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			pixelHeight = std::max(pixelHeight, g->bitmap.rows);
			width += (((g->advance.x) / 64) * scale.x) / Config::pixelPerUnit;
			height = std::max(height, (g->bitmap.rows * scale.y) / Config::pixelPerUnit);

			if (g->bitmap.rows > (unsigned int)g->bitmap_top) {
				baselineGap = std::max(baselineGap, (unsigned int)(g->bitmap.rows - g->bitmap_top));
			}
		}

		Rect textBox {0, 0, width, height};

		pos += (transform->rectTransform->rect.topleft * (float)Config::pixelPerUnit);

		switch (align) {// si parte da bottomleft
			case Align::TOPLEFT:
				pos.y += (transform->rectTransform->rect.height - textBox.height) * (float)Config::pixelPerUnit;
				break;
			case Align::TOPRIGHT:
				pos.y += (transform->rectTransform->rect.height - textBox.height) * (float)Config::pixelPerUnit;
				pos.x += (transform->rectTransform->rect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::BOTTOMLEFT:
				// rimane uguale
				break;
			case Align::BOTTOMRIGHT:
				pos.x += (transform->rectTransform->rect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::LEFT:
				pos.y += ((transform->rectTransform->rect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::RIGHT:
				pos.y += ((transform->rectTransform->rect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				pos.x += (transform->rectTransform->rect.width - textBox.width) * (float)Config::pixelPerUnit;
				break;
			case Align::TOP:
				pos.x += ((transform->rectTransform->rect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				pos.y += (transform->rectTransform->rect.height - textBox.height) * (float)Config::pixelPerUnit;
				break;
			case Align::BOTTOM:
				pos.x += ((transform->rectTransform->rect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::CENTER:
				pos.x += ((transform->rectTransform->rect.width / 2) - (textBox.width / 2)) * (float)Config::pixelPerUnit;
				pos.y += ((transform->rectTransform->rect.height / 2) - (textBox.height / 2)) * (float)Config::pixelPerUnit;
				break;
			case Align::CUSTOM:
			default:
				pos.y += (transform->rectTransform->rect.height - textBox.height) * (float)Config::pixelPerUnit;

		}

		bool baseline;
		if (bottomAlign == BottomAlign::HEIGHT && (align == Align::BOTTOMLEFT || align == Align::BOTTOM || align == Align::BOTTOMRIGHT)) {
			baseline = false;
		}

		for (p = text_.c_str(); *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			float x2 = (pos.x + g->bitmap_left * scale.x) / Config::pixelPerUnit;
			float y2 = (-pos.y - (g->bitmap_top + (baseline ? 0 : baselineGap)) * scale.y) / Config::pixelPerUnit;
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

    void Text::Render() {

		if (!isReady()) return;

		shader->Use();
		shader->SetMVP(transform->uMVP());
		shader->SetM(transform->uM());
		shader->SetRenderColor(color);
		shader->update();

		VAO->Use();

		write(text);

		VAO->Leave();
		shader->Leave();
	}

	void Text::OnDestroy() {

	}

}

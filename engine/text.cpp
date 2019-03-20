#include <iostream>

#include "text.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"
#include "shaders/fontshader.h"
#include "entity.h"
#include "design.h"

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

	int Text::getWidth(string text_) {
		const char* p;
		FT_GlyphSlot g = font->face->glyph;
		float width = 0;
		for (p = text_.c_str(); *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER)) continue;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
			width += (((g->advance.x) / 64) * scale.x);
		}
		return width;
	}

	void Text::write(string text_) {

		vec2 offset_  = offset * (float)pixelPerUnit;
		vec2 pos = offset_;

		const char* p;
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
		unsigned int baselineGap = 0;
		float rectWidth = transform->rectTransform->rect.width * (float)pixelPerUnit;

		map<int, int> words;
		int i = 0;
		int row = 0;

		if (wordWrap) {
			string word = "";

			for (p = text_.c_str(); *p; p++, i++) {
				if (isspace(*p) || *p == '\0') {
					words.insert({i - word.length(), getWidth(word)});
					word = "";
				} else {
					word += *p;
				}
			}
			words.insert({i - word.length(), getWidth(word)});
		}

		i = 0;
		float rowwidth = 0;
		vector<float> rowheight;
		rowheight.push_back(0.0f);
		for (p = text_.c_str(); *p; p++, i++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			rowwidth += (((g->advance.x) / 64) * scale.x);
			rowheight[row] = std::max(rowheight[row], (g->bitmap.rows * scale.y));
			width = std::max(width, rowwidth);

			if (wordWrap && words.find(i + 1) != words.end() && rowwidth + words[i + 1] > rectWidth) {
				row++;
				rowheight.push_back(0.0f);
				rowwidth = 0;
			}

			if (g->bitmap.rows > (unsigned int)g->bitmap_top) {
				baselineGap = std::max(baselineGap, (unsigned int)(g->bitmap.rows - g->bitmap_top));
			}
		}

		if (wordWrap) {
			for (auto h : rowheight) height += h;
			height += (rowheight[0] * lineSpace) * row;
		} else {
			height = rowheight[0];
		}

		pos += (transform->rectTransform->rect.bottomleft * (float)pixelPerUnit);

		vec2 rectPixelSize = transform->rectTransform->rect.size * (float)pixelPerUnit;
		vec2 textPixelSize = {width, height};
		vec2 sizeDelta = rectPixelSize - textPixelSize;

		switch (align) {// si parte da bottomleft
			case Align::TOPLEFT:
				pos.y += sizeDelta.y;
				break;
			case Align::TOPRIGHT:
				pos.y += sizeDelta.y;
				pos.x += sizeDelta.x;
				break;
			case Align::BOTTOMLEFT:
				// rimane uguale
				break;
			case Align::BOTTOMRIGHT:
				pos.x += sizeDelta.x;
				break;
			case Align::LEFT:
				pos.y += sizeDelta.y / 2;
				break;
			case Align::RIGHT:
				pos.y += sizeDelta.y / 2;
				pos.x += sizeDelta.x;
				break;
			case Align::TOP:
				pos.x += sizeDelta.x / 2;
				pos.y += sizeDelta.y;
				break;
			case Align::BOTTOM:
				pos.x += sizeDelta.x / 2;
				break;
			case Align::CENTER:
				pos.x += sizeDelta.x / 2;
				pos.y += sizeDelta.y / 2;
				break;
			case Align::CUSTOM:
			default:
				break;
		}

		float leftpos = pos.x;
		textRect = {pos.x / (float)pixelPerUnit, pos.y / (float)pixelPerUnit, width / (float)pixelPerUnit, height / (float)pixelPerUnit};

		bool baseline;
		if (bottomAlign == BottomAlign::HEIGHT && (align == Align::BOTTOMLEFT || align == Align::BOTTOM || align == Align::BOTTOMRIGHT)) {
			baseline = false;
		}
		bool first = true;
		i = 0;
		row = 0;
		for (p = text_.c_str(); *p; p++, i++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			float x2 = (pos.x + (first && alignToGeometry? 0 : g->bitmap_left) * scale.x) / Config::pixelPerUnit;
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

			first = false;

			if (wordWrap && words.find(i + 1) != words.end() && width + words[i + 1] > transform->rectTransform->rect.width * (float)pixelPerUnit) {
				pos.x = leftpos; first = true;
				pos.y -= ((g->advance.y) / 64) * scale.y + rowheight[row] + (rowheight[0] * lineSpace);
				row++;
			} else {
				pos.x += ((g->advance.x) / 64) * scale.x;
				pos.y += ((g->advance.y) / 64) * scale.y;
			}
		}
		rowheight.clear();
		words.clear();
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

		//RenderMode rm = entity->canvas != nullptr ? entity->canvas->renderMode : RenderMode::WORLD;
		//Design::DrawRect(Transform::VEC3_ZERO, textRect, {1.0f, 0.0f, 0.0f, 1.0f}, DrawMode::HOLLOW, rm, transform->MVP);
	}

	void Text::OnDestroy() {

	}

}

#include <iostream>

#include "textrenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"

namespace se {

    using namespace std;

	TextRenderer::TextRenderer() {
		name = "Font Renderer";
		shader = GLManager::GetShader("Font Shader");

		VAO = new Vao();
	}

	TextRenderer::~TextRenderer() {

	}

	TextRenderer::TextRenderer(string name_) {
		name = name_;
	}

	bool TextRenderer::isReady() {
		return (font != nullptr && shader != nullptr && transform != nullptr);
	}

	void TextRenderer::SetFont(Font* font_) {
	    font = font_;
	}

    void TextRenderer::SetText(std::string text_) {
        _text = text_;
    }

    void TextRenderer::SetScale(glm::fvec2 scale_) {
        _scale = scale_;
    }

    void TextRenderer::SetColor(Color color_) {
        _color = color_;
    }

    void TextRenderer::SetRect(Rect rect_) {
        _rect = rect_;
    }

	void TextRenderer::Awake() {

		shader->awake();

		shader->Use();
		VAO->Init();
	}

	void TextRenderer::Update() {}

	void TextRenderer::write(const char *text, float x, float y, float sx, float sy) {
		const char *p;
		FT_GlyphSlot g = font->face->glyph;

		GLuint tex;
		glGenTextures(1, &tex);
		glActiveTexture(shader->GetTexture("main_texture"));
		glBindTexture(GL_TEXTURE_2D, tex);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		for (p = text; *p; p++) {
			if (FT_Load_Char (font->face, *p, FT_LOAD_RENDER) )
				continue;

			glTexImage2D (GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			float x2 = x + g->bitmap_left * sx;
			float y2 = -y - g->bitmap_top * sy;
			float w = g->bitmap.width * sx;
			float h = g->bitmap.rows * sy;

			vector<vec4> box {
				{ x2,     -y2, 		0, 0 },
				{ x2 + w, -y2, 		1, 0 },
				{ x2,     -y2 - h, 	0, 1 },
				{ x2 + w, -y2 - h, 	1, 1 }
			};

			VAO->SetFontVertices(box, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, VAO->vertexFontBuffer);
			glEnablei(GL_BLEND, VAO->vertexFontBuffer);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glDisablei(GL_BLEND, VAO->vertexFontBuffer);

			x += (g->advance.x / 64) * sx;
			y += (g->advance.y / 64) * sy;
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

		font->setSize(40);
		write(text.c_str(), 0.0f, 0.0f, scale.x, scale.y);

		VAO->Leave();
		shader->Leave();
	}

	void TextRenderer::OnDestroy() {

	}

}

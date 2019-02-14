#include <iostream>

#include "textrenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"

namespace se {

    using namespace std;

	TextRenderer::TextRenderer() {
		name = "Font Renderer";

		shader = new Shader();
		shader->LoadFromString(
			#include "font.vert"
			,
			#include "font.frag"
		);
		shader->name = "Font Shader";

		transform->SetPivot({0.0f, 0.0f});
	}

	TextRenderer::~TextRenderer() {
		if (shader != nullptr) delete(shader);
	}

	TextRenderer::TextRenderer(string name_) {
		name = name_;
	}

	bool TextRenderer::isReady() {
		return (font != nullptr && shader != nullptr && transform != nullptr);
	}

	void TextRenderer::SetFont(Font* font_) {
	    _font = font_;
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

        glUseProgram(shader->GetProgram());

		GLuint tex;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(glGetUniformLocation(shader->GetProgram(), "tex"), 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void TextRenderer::Update() {
	}

	void TextRenderer::write(const char *text, float x, float y, float sx, float sy) {
		const char *p;

		for (p = text; *p; p++) {
			if (FT_Load_Char(font->face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				font->face->glyph->bitmap.width,
				font->face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				font->face->glyph->bitmap.buffer);

			float x2 = x + font->face->glyph->bitmap_left * sx;
			float y2 = -y - font->face->glyph->bitmap_top * sy;
			float w = font->face->glyph->bitmap.width * sx;
			float h = font->face->glyph->bitmap.rows * sy;

			GLfloat box[4][4] = {
				{x2, -y2, 0, 0},
				{x2 + w, -y2, 1, 0},
				{x2, -y2 - h, 0, 1},
				{x2 + w, -y2 - h, 1, 1},
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			x += (font->face->glyph->advance.x / 64) * sx;
			y += (font->face->glyph->advance.y / 64) * sy;
		}
	}

    void TextRenderer::Render() {

        if (!isReady()) return;

        glUseProgram(shader->GetProgram());

        // uniforms
		glUniform4f(glGetUniformLocation(shader->GetProgram(), "color"), color.r, color.g, color.b, color.a);
		glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "MVP"), 1, GL_FALSE, &transform->MVP[0][0]);

		write("The Quick Brown Fox", transform->GetWorldPosition().x, transform->GetWorldPosition().y, scale.x, scale.y);

		glUseProgram(0);
	}

	void TextRenderer::OnDestroy() {
	}

}

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

		glUseProgram(shader->GetProgram());
        attribute_coord = glGetAttribLocation(shader->GetProgram(), "coord");
        // attribute_coord = 0;
        uniform_tex = glGetUniformLocation(shader->GetProgram(), "tex");
        uniform_color = glGetUniformLocation(shader->GetProgram(), "color");
        uniform_mvp = glGetUniformLocation(shader->GetProgram(), "MVP");
        glUseProgram(0);

        glGenBuffers(1, &vbo);
	}

	void TextRenderer::Update() {}

	void TextRenderer::write(const char *text, float x, float y, float sx, float sy) {
		const char *p;
		FT_GlyphSlot g = font->face->glyph;

		GLuint tex;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(uniform_tex, GL_TEXTURE0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

		for (p = text; *p; p++) {
			if (FT_Load_Char (font->face, *p, FT_LOAD_RENDER) )
				continue;

			glTexImage2D (GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			float x2 = x + g->bitmap_left * sx;
			float y2 = -y - g->bitmap_top * sy;
			float w = g->bitmap.width * sx;
			float h = g->bitmap.rows * sy;

			GLfloat box[4][4] = {
				{ x2,     -y2, 		0, 0 },
				{ x2 + w, -y2, 		1, 0 },
				{ x2,     -y2 - h, 	0, 1 },
				{ x2 + w, -y2 - h, 	1, 1 },
			};

			glBufferData (GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
			glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

			x += (g->advance.x / 64) * sx;
			y += (g->advance.y / 64) * sy;
		}

		glDisableVertexAttribArray(attribute_coord);
		glDeleteTextures(1, &tex);
	}

    void TextRenderer::Render() {

		if (!isReady()) return;

		glUseProgram(shader->GetProgram());

		glUniform4f(uniform_color, color.r, color.g, color.b, color.a);
		glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &transform->MVP[0][0]);

		font->setSize(40);
		write(text.c_str(), 0.0f, 0.0f, scale.x, scale.y);

		glUseProgram(0);
	}

	void TextRenderer::OnDestroy() {}

}

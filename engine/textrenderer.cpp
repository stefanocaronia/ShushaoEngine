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

		VAO = new Vao(VBO_FONT);
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

		const char *p;
		FT_GlyphSlot g = font->face->glyph;

		GLuint tex;
		glGenTextures(1, &tex);
		glActiveTexture(shader->GetTexture("main_texture"));
		glBindTexture(GL_TEXTURE_2D, tex);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

			VAO->SetFontVertices(box, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, VAO->vertexFontBuffer->Id);
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

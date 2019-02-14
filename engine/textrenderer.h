#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "color.h"
#include "rect.h"
#include "font.h"
#include "shader.h"

namespace se {

	class TextRenderer : public Renderer {

		public:

			TextRenderer();
			TextRenderer(std::string);
			~TextRenderer();

			Shader* shader = nullptr;

			Font* font = nullptr;

			// readonly properties
			const Color& color = _color;
			const std::string& text = _text;
			const Rect& rect = _rect;

			glm::fvec2& scale = _scale;

			void SetText(std::string);
			void SetColor(Color);
			void SetFont(Font*);
			void SetScale(glm::fvec2);
			void SetRect(Rect);

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

        private:

            SDL_Surface* surface = nullptr;
            SDL_Texture* texture = nullptr;

            bool isReady();

            Rect _rect;
			glm::fvec2 _scale = { 1.0f, 1.0f };
            Color _color = { 1.0f, 1.0f, 1.0f, 1.0f };
            std::string _text = "";
            std::string filename;

            GLint attribute_position;
            GLint uniform_tex;
            GLint uniform_color;
            GLint uniform_mvp;

            GLuint vbo;

            void write(const char*, float, float, float, float);

	};

}

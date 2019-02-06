#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "color.h"
#include "rect.h"

namespace ShushaoEngine {

	class TextRenderer : public Renderer {

		public:

			TextRenderer();
			TextRenderer(std::string);
			~TextRenderer();

			TTF_Font* font = nullptr;

			// readonly properties
			const Color& color = _color;
			const std::string& text = _text;
			const Rect& quad = _quad;

			int fontSize = 24;

			void Load(std::string, int);

			void SetText(std::string);
			void SetColor(Color);
			void SetQuad(Rect);

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

        private:

            SDL_Surface* surface = nullptr;
            SDL_Texture* texture = nullptr;

            Rect _quad;
            Color _color = {1.0f, 1.0f, 1.0f, 1.0f};
            std::string _text = "";

            SDL_Rect sdlquad;
            SDL_Color sdlcolor = {255, 255, 255};
            std::string filename;

            void init();

	};

}

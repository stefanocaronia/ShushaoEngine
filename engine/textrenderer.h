#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "color.h"
#include "rect.h"
#include "font.h"
#include "shader.h"
#include "vao.h"
#include "config.h"
#include "types.h"

// TODO: deve renderizzare più righe? controllare com'è in unity

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
			glm::fvec2& offset = _offset;
			glm::fvec2& scale = _scale;
			const unsigned int& pixelPerUnit = _pixelPerUnit;
			const Align& pivot = _pivot;
			const Align& align = _align;

			TextRenderer* SetText(std::string value) 			{ _text = value; return this;}
			TextRenderer* SetColor(Color value) 				{ _color = value; return this; }
			TextRenderer* SetFont(Font* value) 					{ font = value; return this; }
			TextRenderer* SetScale(glm::fvec2 value) 			{ _scale = value; return this; }
			TextRenderer* SetOffset(glm::fvec2 value) 			{ _offset = value; return this; }
			TextRenderer* SetRect(Rect value) 					{ _rect = value; return this; }
			TextRenderer* SetSize(float value) 					{ font->SetSize(value); return this;}
			TextRenderer* SetPivot(Align value)					{ _pivot = value; return this; }
			TextRenderer* SetAlign(Align value)					{ _align = value; return this; }
			TextRenderer* SetPixelSize(int value) 				{ font->SetPixelSize(value); return this; }
			TextRenderer* SetPixelPerUnit(unsigned int value) 	{ _pixelPerUnit = value; return this; }

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

        private:

            SDL_Surface* surface = nullptr;
            SDL_Texture* texture = nullptr;

            bool isReady();

            Rect _rect;
			unsigned int _pixelPerUnit = Config::pixelPerUnit;
			glm::fvec2 _offset = { 0.0f, 0.0f };
			glm::fvec2 _scale = { 1.0f, 1.0f };
            Color _color = { 1.0f, 1.0f, 1.0f, 1.0f };
            std::string _text = "";
			Align _align = Align::TOPLEFT;
			Align _pivot = Align::TOPLEFT;
            std::string filename;

            GLuint vbo;
            Vao* VAO;

            void write(std::string text_);

	};

}

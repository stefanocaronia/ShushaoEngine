#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "renderer.h"
#include "color.h"
#include "rect.h"
#include "font.h"
#include "shaders/shader.h"
#include "vao.h"
#include "config.h"
#include "types.h"

// TODO: deve renderizzare più righe? controllare com'è in unity

namespace se {

	enum class BottomAlign {
		BASELINE,
		HEIGHT
	};

	class Text : public Renderer {

		public:

			virtual void setup();

			Shader* shader = nullptr;
			Font* font = nullptr;

			// readonly properties
			const Color& color = _color;
			const std::string& text = _text;
			glm::fvec2& offset = _offset;
			glm::fvec2& scale = _scale;
			const unsigned int& pixelPerUnit = _pixelPerUnit;
			const Align& align = _align;
			const BottomAlign& bottomAlign = _bottomAlign;
			bool alignToGeometry = false;
			bool wordWrap = false;

			float lineSpace = 0.3f; // %

			Text* SetText(std::string value) 			{ _text = value; return this;}
			Text* SetColor(Color value) 				{ _color = value; return this; }
			Text* SetFont(Font* value) 					{ font = value; return this; }
			Text* SetScale(glm::fvec2 value) 			{ _scale = value; return this; } // scale locale del carattere (si aggiunge alla scale del transform, decidere se togliere, qual'è la migliore?)
			Text* SetOffset(glm::fvec2 value) 			{ _offset = value; return this; }
			Text* SetSize(float value) 					{ font->SetSize(value); return this;}
			Text* SetBottomAlign(BottomAlign value)		{ _bottomAlign = value; return this; }
			Text* SetAlign(Align value)					{ _align = value; return this; }
			Text* SetPixelSize(int value) 				{ font->SetPixelSize(value); return this; }
			Text* SetPixelPerUnit(unsigned int value) 	{ _pixelPerUnit = value; return this; }

			void Awake();
			void Update();
			void Render();
			void OnDestroy();

			int getWidth(std::string text);

        private:

            SDL_Surface* surface = nullptr;
            SDL_Texture* texture = nullptr;

            bool isReady();

			unsigned int _pixelPerUnit = Config::pixelPerUnit;
			BottomAlign _bottomAlign = BottomAlign::HEIGHT;
			glm::fvec2 _offset = { 0.0f, 0.0f };
			glm::fvec2 _scale = { 1.0f, 1.0f };
            Color _color = { 1.0f, 1.0f, 1.0f, 1.0f };
            std::string _text = "";
			Align _align = Align::TOPLEFT;
            std::string filename;

			Rect textRect;

            GLuint vbo;
            Vao* VAO;

            void write(std::string text_);

	};

}

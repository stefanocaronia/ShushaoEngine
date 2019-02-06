#include <iostream>

#include "textrenderer.h"
#include "glmanager.h"
#include "transform.h"

namespace ShushaoEngine {

    using namespace std;

	TextRenderer::TextRenderer() {
		name = "Font Renderer";
	}

	TextRenderer::~TextRenderer() {}

	TextRenderer::TextRenderer(string name_) {
		name = name_;
	}

	void TextRenderer::Load(string filename_, int fontSize) {
        filename = filename_;
        font = TTF_OpenFont(filename_.c_str(), fontSize);
	}

	void TextRenderer::init() {
	    surface = TTF_RenderText_Solid(font, text.c_str(), sdlcolor);
	    texture = SDL_CreateTextureFromSurface(GLManager::gRenderer, surface);
	    SDL_FreeSurface(surface);
	}

    void TextRenderer::SetText(std::string text_) {
        _text = text_;
    }

    void TextRenderer::SetColor(Color color_) {
        _color = color_;
        sdlcolor = {(Uint8)floor(255 / color_.r), (Uint8)floor(255 / color_.g), (Uint8)floor(255 / color_.b) };
    }

    void TextRenderer::SetQuad(Rect rect_) {
        _quad = rect_;
        sdlquad.x = _quad.x;
        sdlquad.y = _quad.y;
        sdlquad.w = _quad.width;
        sdlquad.h = _quad.height;
    }

	void TextRenderer::Awake() {
        init();
	}

	void TextRenderer::Update() {}

	void TextRenderer::Render() {
	    SDL_Rect translatedRect = sdlquad;
	    translatedRect.x += transform->GetWorldPosition().x;
	    translatedRect.y += transform->GetWorldPosition().y;
	    SDL_RenderCopy(GLManager::gRenderer, texture, NULL, &translatedRect);
	}

	void TextRenderer::OnDestroy() {
	    SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
	}

}

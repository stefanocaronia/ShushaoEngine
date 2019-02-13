#include <iostream>

#include "textrenderer.h"
#include "glmanager.h"
#include "transform.h"
#include "debug.h"

namespace se {

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
        Debug::Log << "Font: " << font << " -> " << endl;
	}

	void TextRenderer::init() {
	    // surface = TTF_RenderText_Solid(font, text.c_str(), sdlcolor);
	    surface = TTF_RenderText_Blended(font, text.c_str(), sdlcolor);
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

	void TextRenderer::Update() {
	    sdlquad_translated.x += transform->GetWorldPosition().x;
	    sdlquad_translated.y += transform->GetWorldPosition().y;
	    sdlquad_translated.w = sdlquad.w;
	    sdlquad_translated.h = sdlquad.h;
	}

	void TextRenderer::Render() {
		SDL_RenderClear(GLManager::gRenderer);
	    SDL_RenderCopy(GLManager::gRenderer, texture, nullptr, &sdlquad_translated);
        SDL_RenderPresent(GLManager::gRenderer);
	}

	void TextRenderer::OnDestroy() {
	    SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
	}

}

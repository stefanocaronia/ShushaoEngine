#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "color.h"
#include "config.h"
#include "globals.h"
#include "rect.h"
#include "renderer.h"

namespace se {

class Shader;
class Font;
class Vao;

class Text : public Renderer {
public:
    enum class BottomAlign {
        BASELINE,
        HEIGHT
    };

    virtual void setup();

    Shader* shader = nullptr;
    Font* font = nullptr;

    // readonly properties
    const Color& color = _color;
    const std::wstring& text = _text;
    glm::fvec2& offset = _offset;
    glm::fvec2& scale = _scale;
    const unsigned int& pixelPerUnit = _pixelPerUnit;
    const Align& align = _align;
    const BottomAlign& bottomAlign = _bottomAlign;
    const bool& alignToGeometry = _alignToGeometry;
    const bool& wordWrap = _wordWrap;
    const float& lineHeight = _lineHeight;  // %

    Text* SetText(std::wstring value);
    Text* SetText(std::wstring value, Color col);
    Text* SetColor(Color value);
    Text* SetFont(Font* value);
    Text* SetScale(glm::fvec2 value);
    Text* SetOffset(glm::fvec2 value);
    Text* SetSize(float unit_size);
    Text* SetSize(int pixel_size);
    Text* SetBottomAlign(BottomAlign value);
    Text* SetAlign(Align value);
    Text* SetPixelSize(int value);
    Text* SetPixelPerUnit(unsigned int value);
    Text* SetLineHeight(float value);
    Text* SetWordWrap(bool value);
    Text* SetAlignToGeometry(bool value);
    Text* Clear();

    void Awake();
    void Render();

    int getWidth(std::wstring text);

private:
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;

    bool isReady();

    unsigned int _pixelPerUnit = Config::pixelPerUnit;
    BottomAlign _bottomAlign = BottomAlign::HEIGHT;
    bool _wordWrap = false;
    bool _alignToGeometry = false;
    glm::fvec2 _offset = {0.0f, 0.0f};
    glm::fvec2 _scale = {1.0f, 1.0f};
    Color _color = {1.0f, 1.0f, 1.0f, 1.0f};
    std::wstring _text = L"";
    Align _align = Align::TOPLEFT;
    float _lineHeight = 1.0f;  // %
    std::string filename;

    float lastYpos = 0.0f;
    float lastHeight = 0.0f;
    unsigned int currentLine = 0;

    Rect textRect;

    GLuint vbo;
    Vao* VAO;

    void writeLine(std::wstring text_, Color color);
};

}  // namespace se

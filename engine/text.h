#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "color.h"
#include "config.h"
#include "font.h"
#include "globals.h"
#include "rect.h"
#include "renderer.h"
#include "shaders/shader.h"
#include "vao.h"

// TODO: deve renderizzare più righe? controllare com'è in unity

namespace se {

class Text : public Renderer {
public:
    enum class BottomAlign {
        BASELINE,
        HEIGHT
    };

    struct Line {
        std::string text;
        Color color = color::white;

        Line(std::string& text_, const Color& color_) : text(text_), color(color_) {}
    };

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

    float lineSpace = 0.3f;  // %

    Text* SetText(std::string value);
    Text* SetText(std::string value, Color col);
    Text* SetColor(Color value);
    Text* SetFont(Font* value);
    Text* SetScale(glm::fvec2 value);
    Text* SetOffset(glm::fvec2 value);
    Text* SetSize(float value);
    Text* SetBottomAlign(BottomAlign value);
    Text* SetAlign(Align value);
    Text* SetPixelSize(int value);
    Text* SetPixelPerUnit(unsigned int value);
    Text* AddLine(Line line_);
    Text* SetLines(std::vector<Line>& lines_);
    Text* SetLinespace(int value);
    Text* Clear();

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
    glm::fvec2 _offset = {0.0f, 0.0f};
    glm::fvec2 _scale = {1.0f, 1.0f};
    Color _color = {1.0f, 1.0f, 1.0f, 1.0f};
    std::string _text = "";
    Align _align = Align::TOPLEFT;
    std::string filename;

    std::vector<Line> lines;

    float lastYpos = 0.0f;

    Rect textRect;

    GLuint vbo;
    Vao* VAO;

    void writeLine(std::string text_, Color color);
};

}  // namespace se

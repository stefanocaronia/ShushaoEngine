#include <iostream>

#include "debug.h"
#include "design.h"
#include "entity.h"
#include "font.h"
#include "glmanager.h"
#include "rect.h"
#include "shaders/fontshader.h"
#include "shaders/shader.h"
#include "text.h"
#include "transform.h"
#include "vao.h"

namespace se {

using namespace std;
using namespace glm;

void Text::setup() {
    entity->transform->isRectTransform = true;
    shader = new FontShader();
    VAO = new Vao();
    VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_FONT);
}

bool Text::isReady() {
    return (font != nullptr && shader != nullptr && transform != nullptr);
}

void Text::Awake() {
    shader->awake();
    VAO->Init();

    if (entity->canvas != nullptr && entity->canvas->renderMode == RenderMode::SCREEN) {
        shader->Use();
        shader->SetVector("viewport", GLManager::VIEWPORT);
        shader->Enable("viewport");
        shader->Leave();
    }
}

int Text::getWidth(std::wstring text_) {
    const wchar_t* p;
    float width = 0;
    for (p = text_.c_str(); *p; p++) {
        if (!font->LoadCharTexture(*p)) {
            continue;
        }
        width += (((font->face->glyph->advance.x) / 64) * scale.x);
    }
    return width;
}

void Text::writeLine(std::wstring text_, Color color) {
    /*
        NB: y punta in alto anche qui, non confondere con il web
    */

    /* FIXME:
        allineamenti left, right e center (allineamento verticale multilinea)
    */

    const wchar_t* p;
    const wchar_t* ctext = text_.c_str();

    shader->SetRenderColor(color);

    // pos di partenza in pixel
    vec2 pos = offset * (float)pixelPerUnit;
    float leftpos = pos.x;

    // calcolo altezza linea e spaziatura utilizzando le percentuali
    int pixelLineHeight = font->size * lineHeight;

    // calcolo il rect transform in pixel
    Rect pixelRect = transform->rectTransform->rect * (float)pixelPerUnit;

    // ottengo il Glyph dal font face
    FT_GlyphSlot glyph = font->face->glyph;

    // genero la texture
    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(shader->GetTextureIndex("diffuse_map"));
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // istanzio variabili
    float width = 0.0f;
    float height = 0.0f;
    unsigned int baselineGap = 0;
    bool baseline = true;
    map<int, int> words;
    size_t i = 0;

    // estraggo tutte le words di una linea
    if (wordWrap) {
        std::wstring word = L"";
        for (p = ctext, i = 0; i < text_.size(); ++p, ++i) {
            if (isspace(*p) || *p == '\0') {
                words.insert({i - word.length(), getWidth(word)});
                word = L"";
            } else {
                word += *p;
            }
        }
        words.insert({i - word.length(), getWidth(word)});
    }

    vector<float> rowwidth;
    rowwidth.push_back(0.0f);
    vector<float> rowheight;
    rowheight.push_back(0.0f);
    int row = 0;

    // ciclo tutti i caratteri della linea per calcolare le dimensioni
    for (p = ctext, i = 0; i < text_.size(); ++p, ++i) {
        if (!font->LoadCharTexture(*p)) {
            continue;
        }

        if (*p != '\n') {
            rowwidth[row] += (((glyph->advance.x) / 64) * scale.x);
            rowheight[row] = std::max(rowheight[row], (glyph->bitmap.rows * scale.y));
            width = std::max(width, rowwidth[row]);
        }

        if (wordWrap && (*p == '\n' || (words.find(i + 1) != words.end() && rowwidth[row] + words[i + 1] > pixelRect.width))) {
            row++;
            rowheight.push_back(0.0f);
            rowwidth.push_back(0.0f);
        }

        if (glyph->bitmap.rows > (unsigned int)glyph->bitmap_top) {
            baselineGap = std::max(baselineGap, (unsigned int)(glyph->bitmap.rows * scale.y - glyph->bitmap_top * scale.y));
        }
    }

    // calcolo l'altezza del testo
    if (wordWrap) {
        for (size_t i = 0; i < rowheight.size(); ++i) {
            height += rowheight[i];
            if (i < rowheight.size() - 1) {
                height += pixelLineHeight - rowheight[i];
            }
        }
    } else {
        height = rowheight[0];
    }

    // linespace
    /* if (currentLine > 1) {
        pos.y -= pixelLineHeight - rowheight[rowheight.size() - 1];
    } */

    // qui aggiungo il bottomleft (?)
    pos += (transform->rectTransform->rect.bottomleft * (float)pixelPerUnit);

    // ricavo il size delta
    vec2 textPixelSize = {width, height};
    vec2 sizeDelta = pixelRect.size - textPixelSize;

    // allineo il testo
    switch (align) {  // si parte da bottomleft
        case Align::TOPLEFT:
            pos.y += pixelRect.size.y - rowheight[0];
            break;
        case Align::TOPRIGHT:
            pos.y += pixelRect.size.y - rowheight[0];
            pos.x += pixelRect.size.x - rowwidth[0];
            break;
        case Align::BOTTOMLEFT:
            // rimane uguale
            pos.y += height - rowheight[0];
            break;
        case Align::BOTTOMRIGHT:
            pos.y += height - rowheight[0];
            pos.x += pixelRect.size.x - rowwidth[0];
            break;
        case Align::LEFT:
            pos.y += (pixelRect.size.y - height) / 2;
            break;
        case Align::RIGHT:
            pos.y += (pixelRect.size.y - height) / 2;
            pos.x += pixelRect.size.x - rowwidth[0];
            break;
        case Align::TOP:
            pos.x += (pixelRect.width - rowwidth[0]) / 2;
            pos.y += pixelRect.size.y - rowheight[0];
            break;
        case Align::BOTTOM:
            pos.y += height - rowheight[0];
            pos.x += (pixelRect.width - rowwidth[0]) / 2;
            break;
        case Align::CENTER:
            pos.x += (pixelRect.width - rowwidth[0]) / 2;
            pos.y += sizeDelta.y / 2;
            break;
        case Align::CUSTOM:
        default:
            break;
    }

    // creo il textRect (debug)
    //textRect = {pos.x / (float)pixelPerUnit, pos.y / (float)pixelPerUnit, width / (float)pixelPerUnit, height / (float)pixelPerUnit};

    if (bottomAlign == BottomAlign::HEIGHT && (align == Align::BOTTOMLEFT || align == Align::BOTTOM || align == Align::BOTTOMRIGHT)) {
        baseline = false;
    }

    bool first = true;
    row = 0;

    /* if (align == Align::TOPRIGHT || align == Align::RIGHT || align == Align::BOTTOMRIGHT) {
        pos.x = leftpos + (pixelRect.width - rowwidth[0]);
    } */

    // ciclo tutti i caratteri per stamparli
    for (p = ctext, i = 0; i < text_.size(); ++p, ++i) {
        if (!font->LoadCharTexture(*p)) {
            continue;
        }

        float xAdjust = (first && alignToGeometry ? 0 : glyph->bitmap_left);
        float yAdjust = (glyph->bitmap_top + (baseline ? 0 : baselineGap));

        float x2 = (pos.x + xAdjust * scale.x) / (float)pixelPerUnit;
        float y2 = -(pos.y + yAdjust * scale.y) / (float)pixelPerUnit;
        float w = (glyph->bitmap.width * scale.x) / (float)pixelPerUnit;
        float h = (glyph->bitmap.rows * scale.y) / (float)pixelPerUnit;

        vector<vec4> box{
            {x2, -y2, 0, 0},
            {x2 + w, -y2, 1, 0},
            {x2, -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1}  //
        };

        first = false;

        if (wordWrap && (*p == '\n' || (words.find(i + 1) != words.end() && rowwidth[row] + words[i + 1] > pixelRect.width))) {
            first = true;

            // allineo il testo successivo
            switch (align) {  // si parte da bottomleft
                case Align::TOPRIGHT:
                    pos.x = pixelRect.size.x - rowwidth[row + 1];
                    break;
                case Align::BOTTOMRIGHT:
                    pos.x = pixelRect.size.x - rowwidth[row + 1];
                    break;
                case Align::RIGHT:
                    pos.x = pixelRect.size.x - rowwidth[row + 1];
                    break;
                case Align::TOP:
                case Align::BOTTOM:
                    pos.x = (pixelRect.width - rowwidth[row + 1]) / 2;
                    break;
                case Align::CENTER:
                    pos.x = (pixelRect.width - rowwidth[row + 1]) / 2;
                    break;
                case Align::CUSTOM:
                case Align::TOPLEFT:
                case Align::BOTTOMLEFT:
                case Align::LEFT:
                    pos.x = leftpos;
                default:
                    break;
            }

            pos.y -= ((glyph->advance.y) / 64) * scale.y + pixelLineHeight;
            row++;
        } else {
            pos.x += ((glyph->advance.x) / 64) * scale.x;
            pos.y += ((glyph->advance.y) / 64) * scale.y;
        }

        if (*p == '\n') continue;

        VAO->Load<vec4>(Vbo::VERTICES, box);
        VAO->GetBuffer(Vbo::VERTICES)->Bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        VAO->GetBuffer(Vbo::VERTICES)->Unbind();
    }

    words.clear();
    glDeleteTextures(1, &tex);
}

void Text::Render() {
    if (!isReady()) return;

    // currentLine = 0;
    // lastYpos = 0.0f;

    shader->Use();
    shader->SetMVP(transform->uMVP());
    shader->SetM(transform->uM());
    shader->SetRenderColor(color);
    shader->update();

    VAO->Use();

    //for (auto& line : lines) {
    writeLine(text, color);
    //}

    VAO->Leave();
    shader->Leave();

    // RenderMode rm = entity->canvas != nullptr ? entity->canvas->renderMode : RenderMode::WORLD;
    // Design::DrawRect(Transform::VEC3_ZERO, textRect, {0.0f, 1.0f, 0.0f, 1.0f}, 1, DrawMode::HOLLOW, rm, transform->MVP);
}

Text* Text::SetText(std::wstring value, Color col) {
    _text = value;
    _color = col;
    return this;
}

Text* Text::SetText(std::wstring value) {
    _text = value;
    return this;
}

Text* Text::SetColor(Color value) {
    _color = value;
    return this;
}

Text* Text::SetFont(Font* value) {
    font = value;
    return this;
}

Text* Text::SetWordWrap(bool value) {
    _wordWrap = value;
    return this;
}

Text* Text::SetAlignToGeometry(bool value) {
    _alignToGeometry = value;
    return this;
}

Text* Text::SetScale(glm::fvec2 value) {  // scale locale del carattere (si aggiunge alla scale del transform, decidere se togliere, qual'è la migliore?)
    _scale = value;
    return this;
}

Text* Text::SetOffset(glm::fvec2 value) {
    _offset = value;
    return this;
}

Text* Text::SetSize(float unit_size) {
    font->SetSize(unit_size);
    return this;
}

Text* Text::SetSize(int pixel_size) {
    font->SetSize(pixel_size / (float)pixelPerUnit);
    return this;
}

Text* Text::SetBottomAlign(BottomAlign value) {
    _bottomAlign = value;
    return this;
}

Text* Text::SetAlign(Align value) {
    _align = value;
    return this;
}

Text* Text::SetPixelSize(int value) {
    font->SetPixelSize(value);
    return this;
}

Text* Text::SetLineHeight(float value) {
    _lineHeight = value;
    return this;
}

Text* Text::SetPixelPerUnit(unsigned int value) {
    _pixelPerUnit = value;
    return this;
}

Text* Text::Clear() {
    _text = L"";
    return this;
}

}  // namespace se

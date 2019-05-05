#pragma once

#include "Shushao/Core.h"
#include "sepch.h"

#include "object.h"
#include "resource.h"

namespace se {

class SHUSHAO_API Font : public Object, public Resource {
public:
    Font(std::string filename = "", std::string n = "");
    ~Font();

    FT_Face face;

    // readonly
    const int& size = _size;

    bool Load(std::string);
    bool LoadEmbedded(int IDRES, std::string library = "");
    void SetSize(float);
    void SetPixelSize(int);

    bool LoadCharTexture(const wchar_t p);

private:
    int _size = 12;  // pixel size

    FT_Byte* bytes = nullptr;

    void init();
};

}  // namespace se

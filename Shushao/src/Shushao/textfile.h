#pragma once

#include "core.h"

#include "object.h"
#include "resource.h"

namespace se {

class SHUSHAO_API Textfile : public Object, public Resource {
public:
    Textfile(std::string filename = "", std::string n = "");

    ~Textfile();

    std::string text;
    std::stringstream buffer;

    bool Load(std::string);
    bool LoadEmbedded(int IDRES, std::string library = "");
};

}  // namespace se

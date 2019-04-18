#pragma once

#include <std_.h>

namespace se {

class LevelMap : private std::vector<std::string> {
public:
    using vector::at;
    using vector::begin;
    using vector::end;

    LevelMap();
    LevelMap(std::initializer_list<std::string>);
    LevelMap(vector<std::string> list);
    void operator=(std::initializer_list<std::string>);
    void operator+=(std::string);
    void operator-=(std::string);
    int operator[](std::string);
    std::string operator[](unsigned int);
    void setDefaults(std::initializer_list<std::string>);
    void setMaxElements(unsigned int);
    int top();
    int over();
    void toString(std::string title = "");

private:
    unsigned int maxElements = 32;
    std::vector<std::string> defaults = {
        "Default"};
};

}  // namespace se

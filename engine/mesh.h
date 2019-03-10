#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "object.h"
#include "texture.h"
#include "vao.h"

namespace se {

    class Mesh : public Object {

        public:

            Mesh();
            Mesh(std::string objfilename);
            ~Mesh();

			Vao* VAO = nullptr;

            std::vector<glm::vec3> vertexData;
            std::vector<glm::vec2> uvData;
            std::vector<glm::vec3> normalsData;
            std::vector<GLushort> indexesData;

			bool ready = false;

            Mesh* Init();
            Mesh* Load(std::string objectFile);

            void PrintData();

    };

}
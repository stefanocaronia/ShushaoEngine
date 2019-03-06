#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "utility.h"
#include "mesh.h"

namespace se {

    using namespace std;
    using namespace glm;

    Mesh::Mesh() {
        name = "Mesh";
        Init();
    }

    Mesh::Mesh(string filename_) {
        name = util::basename(filename_);
        Init();
        Load(filename_);
	}

    Mesh::~Mesh() {
        /* delete (VAO);
        VAO = nullptr; */
    }

    Mesh* Mesh::Init() {
        VAO = new Vao();
        VAO->AddBuffer("vertex", VBO_CONFIG_VERTEX);
        VAO->AddBuffer("uv", VBO_CONFIG_UV);
        VAO->AddBuffer("normal", VBO_CONFIG_NORMAL);
        VAO->AddBuffer("index", VBO_CONFIG_INDEX);
        VAO->Init();
        return this;
    }

    Mesh* Mesh::Load(string filename) {

        std::vector<GLushort> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        FILE* file = fopen(filename.c_str(), "r");
        if (file == NULL) {
            Debug::Log(ERROR) << "Impossible to open the file " << filename << endl;
            return this;
        }

        while (1) {
            char lineHeader[128];

            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) break;  // EOF = End Of File. Quit the loop.

            // Vertices
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);

            // UV Map
            } else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                temp_uvs.push_back(uv);

            // Normals
            } else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);

            // Faces
            } else if (strcmp(lineHeader, "f") == 0) {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                );
                if (matches != 9) {
                    Debug::Log(ERROR) << "File can't be read by our simple parser: Try exporting with other options" << endl;
                    return this;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
            vertexData.push_back(vertex);
            indexesData.push_back(vertexIndices[i]);
        }

        // For each vertex of each triangle
        if (uvIndices.size() > 0)
            for (unsigned int i = 0; i < uvIndices.size(); i++) {
                glm::vec2 uv = temp_uvs[uvIndices[i] - 1];
                uvData.push_back(uv);
            }

        // For each vertex of each triangle
        if (normalIndices.size() > 0)
            for (unsigned int i = 0; i < normalIndices.size(); i++) {
                glm::vec3 normal = temp_normals[normalIndices[i] - 1];
                normalsData.push_back(normal);
            }

        VAO->Use();
		VAO->Load<vec3>("vertex", vertexData);
		VAO->Load<GLushort>("index", indexesData);
		if (uvData.size() > 0)      VAO->Load<vec2>("uv", uvData);
		if (normalsData.size() > 0) VAO->Load<vec3>("normal", normalsData);
		VAO->Leave();

        ready = true;
        return this;
    }

}  // namespace se
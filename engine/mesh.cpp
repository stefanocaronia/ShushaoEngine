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
        delete (VAO);
        VAO = nullptr;
    }

    Mesh* Mesh::Init() {
        VAO = new Vao();
        VAO->AddBuffer(Vbo::VERTICES, VBO_CONFIG_VERTEX);
        VAO->AddBuffer(Vbo::UV, VBO_CONFIG_UV);
        VAO->AddBuffer(Vbo::NORMALS, VBO_CONFIG_NORMAL);
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

        while (true) {

            char lineHeader[128];

            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) break;

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
        }

        // For each vertex of each triangle
        if (uvIndices.size() > 0)
            for (unsigned int i = 0; i < uvIndices.size(); i++) {
                unsigned int uvIndex = uvIndices[i];
                glm::vec2 uv = temp_uvs[uvIndex - 1];
                uvData.push_back(uv.x);
                uvData.push_back(uv.y);
            }

        // For each vertex of each triangle
        if (normalIndices.size() > 0)
            for (unsigned int i = 0; i < normalIndices.size(); i++) {
                unsigned int normalIndex = normalIndices[i];
                glm::vec3 normal = temp_normals[normalIndex - 1];
                normalsData.push_back(normal);
            }

        // For each triangle
        /* for (unsigned int v = 0; v < vertexIndices.size(); v += 3) {
            // For each vertex of the triangle
            for (unsigned int i = 0; i < 3; i += 1) {
                unsigned int vertexIndex = vertexIndices[v + i];
                glm::vec3 vertex = temp_vertices[vertexIndex - 1];

                unsigned int uvIndex = uvIndices[v + i];
                glm::vec2 uv = temp_uvs[uvIndex - 1];

                unsigned int normalIndex = normalIndices[v + i];
                glm::vec3 normal = temp_normals[normalIndex - 1];

                vertexData.push_back(vertex);
                uvData.push_back(uv);
                normalsData.push_back(normal);
            }
        } */


        /* vertexData = {
				{-1.0f, -1.0f, 0.0f},  	// Bottom-left
				{ 1.0f, -1.0f, 0.0f}, 	// Bottom-right
				{ 1.0f,  1.0f, 0.0f}, 	// Top-right
				{-1.0f,  1.0f, 0.0f} 	// Top-left
			};

		uvData = {
				0.0f, 1.0f, // Bottom-left of texture
				1.0f, 1.0f, // Bottom-right of texture
				1.0f, 0.0f, // Top-Right of texture
				0.0f, 0.0f 	// Top-left of texture
			};
 */

        VAO->Use();
		VAO->Load<vec3>(Vbo::VERTICES, vertexData);
		VAO->Load<GLclampd>(Vbo::UV, uvData);
		VAO->Load<vec3>(Vbo::NORMALS, normalsData);
		VAO->Leave();

        ready = true;
        return this;
    }

} // namespace se
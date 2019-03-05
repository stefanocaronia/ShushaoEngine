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

        ifstream in(filename, ios::in);
        if (!in) {
            Debug::Log(ERROR) << "Cannot open " << filename << endl; exit(1);
        }

        string line;
        while (getline(in, line)) {
            string type = line.substr(0,2);
            //const char* values = line.substr(2).c_str();

            // vertices
            if (type == "v ") {
                istringstream s(line.substr(2));
                glm::vec3 v; s >> v.x; s >> v.y; s >> v.z; // v.w = 1.0f;
                vertexData.push_back(v);

            // normals
            } else if (type == "vn") {
                istringstream s(line.substr(2));
                glm::vec3 v; s >> v.x; s >> v.y; s >> v.z; // v.w = 1.0f;
                normalsData.push_back(v);

            // uv
            } else if (type == "vt") {
                istringstream s(line.substr(2));
                glm::vec2 v; s >> v.x; s >> v.y;
                uvData.push_back(v);

            //indexes
            } else if (type == "f ") {
                istringstream s(line.substr(2));
                GLushort a, b, c;
                s >> a; s >> b; s >> c;
                a--; b--; c--;
                indexesData.push_back(a);
                indexesData.push_back(b);
                indexesData.push_back(c);

            } else if (line[0] == '#') {
                /* ignoring this line */
            }
        }

        if (normalsData.size() == 0) {
            normalsData.resize(vertexData.size(), glm::vec3(0.0, 0.0, 0.0));
            int indexSize = (int)indexesData.size();
            for (int i = 0; i < indexSize; i+=3) {
                GLushort ia = indexesData[i];
                GLushort ib = indexesData[i+1];
                GLushort ic = indexesData[i+2];
                glm::vec3 normal = glm::normalize(glm::cross(
                    glm::vec3(vertexData[ib]) - glm::vec3(vertexData[ia]),
                    glm::vec3(vertexData[ic]) - glm::vec3(vertexData[ia])
                ));
                normalsData[ia] = normalsData[ib] = normalsData[ic] = normal;
            }
        }

        VAO->Use();
		VAO->Load<vec3>("vertex", vertexData);
		if (indexesData.size() > 0) VAO->Load<GLushort>("index", indexesData);
		if (uvData.size() > 0)      VAO->Load<vec2>("uv", uvData);
		if (normalsData.size() > 0) VAO->Load<vec3>("normal", normalsData);
		VAO->Leave();

        ready = true;
        return this;
    }

}  // namespace se
#include  <iostream>

#include "libs.h"
#include "model.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	Model::Model() {
	}

	bool Model::loadObject(string objectFile) { // const char*

		vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		vector<vec3> temp_vertices;
		vector<vec2> temp_uvs;
		vector<vec3> temp_normals;

		FILE * file = fopen(objectFile.c_str(), "r");
		if( file == NULL ) {
			cout << "Impossible to open the file " << objectFile << endl;
			return false;
		}

		while( 1 ) {

			char lineHeader[128];

			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) break; // EOF = End Of File. Quit the loop.

			if ( strcmp( lineHeader, "v" ) == 0 ) {
				vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
			} else if ( strcmp( lineHeader, "vt" ) == 0 ) {
				vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				temp_uvs.push_back(uv);
			} else if ( strcmp( lineHeader, "vn" ) == 0 ) {
				vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			} else if ( strcmp( lineHeader, "f" ) == 0 ) {
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
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
		for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
			vec3 vertex = temp_vertices[ vertexIndices[i]-1 ];
			vertexData.push_back(vertex);
		}

		// For each vertex of each triangle
		if (uvIndices.size()>0) for( unsigned int i=0; i<uvIndices.size(); i++ ) {
			unsigned int uvIndex = uvIndices[i];
			vec2 uv = temp_uvs[ uvIndex-1 ];
			uvData.push_back(uv);
		}

		// For each vertex of each triangle
		if (normalIndices.size()>0) for( unsigned int i=0; i<normalIndices.size(); i++ ) {
			unsigned int normalIndex = normalIndices[i];
			vec3 normal = temp_normals[ normalIndex-1 ];
			normalsData.push_back(normal);
		}


		return true;
	}

	bool Model::loadTexture(string textureFile) {

		texture->Load(textureFile);

		return true;

		/*Surface = IMG_Load(textureFile);

		int Mode = GL_RGB;
		if(Surface->format->BytesPerPixel == 4) Mode = GL_RGBA;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		return true;*/
	}

	bool Model::setVertexData(const GLfloat * data, int size) {
		for (unsigned int i=0; i<=(size/sizeof(GLfloat)); i+=3) {
			if (i>0) vertexData.push_back(vec3(data[i-3], data[i-2], data[i-1]));
		}
		return true;
	}

	bool Model::setVertexData(vector<vec3> data) {
		vertexData=data;
		return true;
	}

	bool Model::setUvData(const GLfloat * data, int size) {
		for (unsigned int i=0; i<=(size/sizeof(GLfloat)); i+=2) {
			if (i>0) uvData.push_back(vec2(data[i-2],data[i-1]));
		}
		return true;
	}

	bool Model::setUvData(vector<vec2> data) {
		uvData=data;
		return true;
	}

	bool Model::init() {

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(vec3), &vertexData[0], GL_DYNAMIC_DRAW); // TODO GL_STATIC_DRAW

		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(vec2), &uvData[0], GL_DYNAMIC_DRAW); // TODO GL_STATIC_DRAW

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER,  uvBuffer);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		glBindVertexArray(0);

		return true;
	}

}

#include "shaderprogram.h"
#include "libs.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace ShushaoEngine {

	ShaderProgram::ShaderProgram(string shaderfile) {
		load(shaderfile);
	}

	ShaderProgram::ShaderProgram() {
	}

	ShaderProgram::~ShaderProgram(){
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}

	GLuint ShaderProgram::getProgram() {
		if (programID > 0)
			return programID;
		if (!ShaderProgram::compile()) {
			if (debug) fprintf(stdout, "Error Compiling ShaderProgram \n");
			return 0;
		}
		if (!ShaderProgram::link()) {
			if (debug) fprintf(stdout, "Error Linking ShaderProgram \n");
			return 0;
		}
		return programID;
	}

	bool ShaderProgram::compile() {

		// Compile Vertex Shader
		if (debug) printf("Compiling Vertex Shader\n");
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(VertexShaderID))
			return false;

		// Compile Fragment Shader
		if (debug) printf("Compiling Fragment shader\n");
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(FragmentShaderID))
			return false;

		return true;
	}

	bool ShaderProgram::link() {

		if (debug) fprintf(stdout, "Linking program\n");

		// Link the program
		programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		if (!programCompilationLog(programID))
			return false;

		return true;
	}

	bool ShaderProgram::load(string shaderfile) {


		string vert = shadersPath + shaderfile + ".vert";
		string frag = shadersPath + shaderfile + ".frag";

		// Read the Vertex Shader code from the file
		ifstream VertexShaderStream(vert.c_str(), ifstream::in);
		if(VertexShaderStream.is_open()) {
			string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();

		} else {
			if (debug) cout << "Impossibile aprire il file " << vert.c_str() << endl;
		}

		// Read the Fragment Shader code from the file
		ifstream FragmentShaderStream(frag.c_str(), ifstream::in);
		if(FragmentShaderStream.is_open()) {
			string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		} else {
			if (debug) cout << "Impossibile aprire il file " << frag.c_str() << endl;
		}

		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		return true;
	}

	bool ShaderProgram::shaderCompilationLog(const GLuint &shader) {
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			if (debug) printf("- Shader Compilation log:\n%s", infoLog);

			/*GLint infoLogLength;
			glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
			if (debug) printf("- Shader Compilation log:\n%s", infoLog);
			delete [] infoLog;*/
			return false;
		}
		return true;
	}

	bool ShaderProgram::programCompilationLog(const GLuint &program) {
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLogLength;
			glGetProgramiv (program, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog= new GLchar[infoLogLength];
			glGetProgramInfoLog (program, infoLogLength, NULL, infoLog);
			if (debug) printf("- Program Compilation log:\n%s", infoLog);
			delete [] infoLog;
			return false;
		}
		return true;
	}

}
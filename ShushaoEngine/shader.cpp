#include <iostream>
#include <fstream>

#include "utility.h"
#include "shader.h"
#include "libs.h"
#include "debug.h"

using namespace std;

namespace ShushaoEngine {

	Shader::Shader() {
		loadWithName("shaders/standard", "Shader Standard");
	}

	Shader::Shader(string filename, string n) {
		loadWithName(filename, n);
	}

	Shader::Shader(string filename) {
		loadWithName(filename, Utility::basename(filename));
	}

	bool Shader::loadWithName(string filename, string n) {
		if (Load(filename)) {
			name = n;
			Init();
			return true;
		}
		return false;
	}

	Shader::~Shader(){

		glUseProgram(0);
		if (VertexShaderID > 0) glDeleteShader(VertexShaderID);
		if (FragmentShaderID > 0) glDeleteShader(FragmentShaderID);
		if (programID > 0) glDeleteProgram(programID);
	}

	bool Shader::Init() {
		if (programID > 0) {
			glUseProgram(0);
			glDeleteProgram(programID);
		}

		if (!Shader::compile()) {
			LOG(ERROR, "Error Compiling Shader");
			return false;
		}
		if (!Shader::link()) {
			LOG(ERROR, "Error Linking Shader");
			return false;
		}

		return true;
	}

	GLuint Shader::getProgram() {

		if (programID > 0)
			return programID;

		if (Init())
			return programID;

		return 0;
	}

	bool Shader::compile() {

		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Compile Vertex Shader
		LOG(INFO, "Compiling Vertex Shader");
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(VertexShaderID))
			return false;

		// Compile Fragment Shader
		LOG(INFO, "Compiling Fragment shader");
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(FragmentShaderID))
			return false;

		return true;
	}

	bool Shader::link() {

		LOG(INFO, "Linking program"); //fprintf(stdout, "Linking program\n");

		// Link the program
		programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		if (!programCompilationLog(programID))
			return false;

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return true;
	}

	bool Shader::Load(string shaderfile) {

		string vert = shaderfile + ".vert";
		string frag = shaderfile + ".frag";

		// Read the Vertex Shader code from the file
		ifstream VertexShaderStream(vert.c_str(), ifstream::in);
		if(VertexShaderStream.is_open()) {
			string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();

		} else {
			LOG(ERROR, "Impossibile aprire il file " + Utility::toString(vert));
		}

		// Read the Fragment Shader code from the file
		ifstream FragmentShaderStream(frag.c_str(), ifstream::in);
		if(FragmentShaderStream.is_open()) {
			string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		} else {
			LOG(ERROR, "Impossibile aprire il file " + Utility::toString(frag));
		}

		return true;
	}

	bool Shader::shaderCompilationLog(const GLuint &shader) {
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			if (Debug::Enabled) LOG(INFO, infoLog);//printf("- Shader Compilation log:\n%s", infoLog);

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

	bool Shader::programCompilationLog(const GLuint &program) {
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLogLength;
			glGetProgramiv (program, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog= new GLchar[infoLogLength];
			glGetProgramInfoLog (program, infoLogLength, NULL, infoLog);
			if (Debug::Enabled) LOG(INFO, infoLog);; //printf("- Program Compilation log:\n%s", infoLog);
			delete [] infoLog;
			return false;
		}
		return true;
	}


}

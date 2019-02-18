#include <iostream>
#include <fstream>

#include "shader.h"
#include "debug.h"
#include "utility.h"

namespace se {

	Shader::Shader() {

		LoadFromString(
			#include "standard.vert"
			,
			#include "standard.frag"
		);

		name = "Standard";
	}

	Shader::Shader(std::string filename, std::string n) {
		loadWithName(filename, n);
	}

	Shader::Shader(std::string filename) {
		loadWithName(filename, util::basename(filename));
	}

	bool Shader::loadWithName(std::string filename, std::string n) {
		if (Load(filename)) {
			name = n;
			Init();
			return true;
		}
		return false;
	}

	Shader::~Shader(){
		Debug::Log << "Destructor di Shader " << name << std::endl;
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
			Debug::Log(ERROR, SOURCE) << "Error Compiling Shader" << endl;
			return false;
		}
		if (!Shader::link()) {
			Debug::Log(ERROR, SOURCE) << "Error Linking Shader" << endl;
			return false;
		}

		//glUseProgram(programID);

		aCoord = glGetAttribLocation(programID, "aCoord");
		aTextureCoord = glGetAttribLocation(programID, "aTextureCoord");
		aColor = glGetAttribLocation(programID, "aColor");

		uMvp = glGetUniformLocation(programID, "uMvp");
		uTextureId = glGetUniformLocation(programID, "uTextureId");
		uColor = glGetUniformLocation(programID, "uColor");

		//glUseProgram(0);

		return true;
	}

	GLuint Shader::GetProgram() {

		if (programID > 0)
			return programID;
		else if (Init())
			return programID;

		return 0;
	}

	void Shader::awake() {
		using namespace std;

		GLuint programID = GetProgram();
		if (!programID) return;

		Awake();
	}

	void Shader::render() {

		glUniform4f(uColor, color.r, color.g, color.b, color.a);
		glUniform1i(uTextureId, texture);
		glUniformMatrix4fv(uMvp, 1, GL_FALSE, mvp);

		Render();
	}

	void Shader::exit() {

		Exit();

		glUseProgram(0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	bool Shader::compile() {

		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Compile Vertex Shader
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(VertexShaderID))
			return false;

		// Compile Fragment Shader
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		// Check Vertex Shader
		if (!shaderCompilationLog(FragmentShaderID))
			return false;

		return true;
	}

	bool Shader::link() {

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

	void Shader::LoadFromString(std::string vsc, std::string fsc) {
		VertexShaderCode = vsc;
		FragmentShaderCode = fsc;
	}

	bool Shader::Load(std::string shaderfile) {

		std::string vert = shaderfile + ".vert";
		std::string frag = shaderfile + ".frag";

		// Read the Vertex Shader code from the file
		ifstream VertexShaderStream(vert.c_str(), ifstream::in);
		if(VertexShaderStream.is_open()) {
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();

		} else {
			Debug::Log(ERROR, SOURCE) << "Impossibile aprire il file " << vert << endl;
		}

		// Read the Fragment Shader code from the file
		ifstream FragmentShaderStream(frag.c_str(), ifstream::in);
		if(FragmentShaderStream.is_open()) {
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		} else {
			Debug::Log(ERROR, SOURCE) << "Impossibile aprire il file " << frag << endl;
		}

		return true;
	}

	bool Shader::shaderCompilationLog(const GLuint &shader) {
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			Debug::Log << "- Shader " << name << " Compilation log:\n" << infoLog;
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
			Debug::Log << "- Program " << name << " Compilation log:\n" << infoLog;
			delete [] infoLog;
			return false;
		}
		return true;
	}

	void Shader::Awake() {}

	void Shader::Render() {}

	void Shader::Exit() {}
}

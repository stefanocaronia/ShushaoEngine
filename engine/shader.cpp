#include <iostream>
#include <fstream>

#include "shader.h"
#include "debug.h"
#include "utility.h"

namespace se {

	//{ #region uniform

	void Uniform::SetFloat(GLfloat& value) {
		glUniform1f(location, value);
	}

	void Uniform::SetInteger(GLint& value) {
		glUniform1i(location, value);
	}

	void Uniform::SetTexture(GLenum& value) {
		glUniform1i(location, value);
	}

	void Uniform::SetMatrix(GLfloat* value) {
		glUniformMatrix4fv(location, 1, GL_FALSE, value);
	}

	void Uniform::SetVector(glm::vec4& value) {
		glUniform4f(location, value.x,  value.y,  value.z,  value.w);
	}

	void Uniform::SetVector(glm::vec3& value) {
		glUniform3f(location, value.x,  value.y,  value.z);
	}

	void Uniform::SetColor(Color& value) {
		glUniform4f(location, value.r,  value.g,  value.b,  value.a);
	}

	//}

	Shader::Shader() {
		name = "Shader";
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

		uniforms.clear();
		Leave();

		if (VertexShaderID > 0) glDeleteShader(VertexShaderID);
		if (FragmentShaderID > 0) glDeleteShader(FragmentShaderID);
		if (programID > 0) glDeleteProgram(programID);
	}

	bool Shader::Init() {
		if (programID > 0) {
			Leave();
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

		// base uniforms
		AddUniform("Model View Projection", "MVP", UniformType::MATRIX, ShaderLocation::LOCATION_MVP, true);
		AddUniform("Render Color", "render_color", UniformType::COLOR, ShaderLocation::LOCATION_RENDER_COLOR, true);
		AddUniform("Main Texture", 	"diffuse_map", UniformType::TEXTURE, ShaderLocation::LOCATION_DIFFUSE_MAP);

		return true;
	}

	void Shader::AddUniform(std::string name_, std::string var_, UniformType type_, GLuint location_, bool locked_) {
		uniforms.insert(pair<string, Uniform>(var_, { name_, var_, type_, location_, locked_ }));
	}

	void Shader::AddUniform(std::string var_, UniformType type_, GLuint location_, bool locked_) {
		uniforms.insert(pair<string, Uniform>(var_, { var_, var_, type_, location_, locked_ }));
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

		for (auto& it : uniforms) {
			if (!it.second.location) {
				it.second.location = glGetUniformLocation(programID, it.first.c_str());
			}
		}
	}

	void Shader::update() {
		Update();
	}

	void Shader::exit() {
		Exit();
		Leave();
	}

	void Shader::Awake() {}
	void Shader::Update() {}
	void Shader::Exit() {}

	//{ #region compile

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

	//}

	//{ #region uniform setter

	void Shader::SetFloat(string var_, GLfloat value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetFloat(value);
	}

	void Shader::SetInteger(string var_, GLint value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetInteger(value);
	}

	void Shader::SetTexture(string var_, GLenum value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetTexture(value);
	}

	void Shader::SetMatrix(string var_, GLfloat* value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetMatrix(value);
	}

	void Shader::SetVector(string var_, glm::vec3 value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetVector(value);
	}

	void Shader::SetVector(string var_, glm::vec4 value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetVector(value);
	}

	void Shader::SetColor(string var_, Color value) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) it->second.SetColor(value);
	}

	GLenum Shader::GetTexture(string var_) {
		auto it = uniforms.find(var_);
		if (it != uniforms.end()) return it->second.texture;
		return 0;
	}

	void Shader::SetMVP(GLfloat* value) {
		SetMatrix("MVP", value);
	}

	void Shader::SetRenderColor(Color value) {
		SetColor("render_color", value);
	}

	//}


}

#include "GLShader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

using std::cout;
using std::endl;

void CheckForErrors(GLuint id, std::string type);

GLShader::GLShader()
{
}

GLShader::~GLShader()
{
}

void GLShader::Compile(const GLchar* vs, const GLchar* fs) {
	this->VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->VertexShader, 1, &vs, nullptr);
	glCompileShader(this->VertexShader);
	CheckForErrors(this->VertexShader, "VERTEXSHADER");

	this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->FragmentShader, 1, &fs, nullptr);
	glCompileShader(this->FragmentShader);
	CheckForErrors(this->FragmentShader, "FRAGMENTSHADER");

	this->Program = glCreateProgram();
	glAttachShader(this->Program, this->VertexShader);
	glAttachShader(this->Program, this->FragmentShader);
	glLinkProgram(this->Program);
	CheckForErrors(this->Program, "PROGRAM");

	glDeleteShader(this->VertexShader);
	glDeleteShader(this->FragmentShader);
}

GLShader& GLShader::Use() {
	glUseProgram(this->Program);
	return *this;
}

void GLShader::SetInt	(const GLchar* name, GLint i, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniform1i(glGetUniformLocation(this->Program, name), i);
}

void GLShader::SetFloat	(const GLchar* name, GLfloat f, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniform1f(glGetUniformLocation(this->Program, name), f);
}

void GLShader::SetVec2	(const GLchar* name, glm::vec2 vec2, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniform2f(glGetUniformLocation(this->Program, name), vec2.x, vec2.y);
}

void GLShader::SetVec3	(const GLchar* name, glm::vec3 vec3, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniform3f(glGetUniformLocation(this->Program, name), vec3.x, vec3.y, vec3.z);
}

void GLShader::SetVec4	(const GLchar* name, glm::vec4 vec4, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->Program, name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void GLShader::SetMat4	(const GLchar* name, glm::mat4 mat4, GLboolean use_shader) {
	if(use_shader) {
		this->Use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(mat4));
}

void CheckForErrors(GLuint id, std::string type) {
	GLint success;
	GLchar log[1024];
	if(type != "PROGRAM") {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(id, 1024, nullptr, log);
			cout << "Shader compile time error. Type: " << type << endl << log << endl;
		}
	} else {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(id, 1024, nullptr, log);
			cout << "Program link time error. Type: " << type << endl << log << endl;
		}
	}
}

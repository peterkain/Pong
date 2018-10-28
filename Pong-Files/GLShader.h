#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class GLShader
{
public:
	GLShader();
	~GLShader();

	GLShader& Use();
	void Compile(const GLchar* vs, const GLchar* fs);

	void SetInt		(const GLchar* name,	GLint i,			GLboolean use_shader = GL_FALSE);
	void SetFloat	(const GLchar* name,	GLfloat i,			GLboolean use_shader = GL_FALSE);
	void SetVec2	(const GLchar* name,	glm::vec2 vec2,		GLboolean use_shader = GL_FALSE);
	void SetVec3	(const GLchar* name,	glm::vec3 vec3,		GLboolean use_shader = GL_FALSE);
	void SetVec4	(const GLchar* name,	glm::vec4 vec4,		GLboolean use_shader = GL_FALSE);
	void SetMat4	(const GLchar* name,	glm::mat4 mat4,		GLboolean use_shader = GL_FALSE);

	GLuint Program;

private:
	GLuint VertexShader, FragmentShader;
};


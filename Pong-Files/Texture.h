#pragma once

#include <GL/glew.h>

struct Texture
{
	Texture();
	~Texture();

	void Create(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

	GLuint ID;
	GLuint Width, Height;
	GLuint Wrap_S, Wrap_T;
	GLuint Filter_MIN, Filter_MAG;
	GLuint Internal_Format, Image_Format;
};


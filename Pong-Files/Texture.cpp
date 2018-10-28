#include "Texture.h"

Texture::Texture() :
	Width{ 0 },
	Height{ 0 },
	Wrap_S{ GL_REPEAT },
	Wrap_T{ GL_REPEAT },
	Filter_MIN{ GL_LINEAR },
	Filter_MAG{ GL_LINEAR },
	Internal_Format{ GL_RGB },
	Image_Format{ GL_RGB }
{
	glGenTextures(1, &this->ID);
}

Texture::~Texture()
{
}

void Texture::Create(GLuint width, GLuint height, unsigned char* data) {
	this->Width = width;
	this->Height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(
		GL_TEXTURE_2D, 0, this->Internal_Format,
		this->Width, this->Height, 0,
		this->Image_Format, GL_UNSIGNED_BYTE, data
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_MIN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_MAG);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
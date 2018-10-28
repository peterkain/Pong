#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include "GLShader.h"
#include "Texture.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static std::map<std::string, GLShader> Shaders;
	static std::map<std::string, Texture> Textures;

	static GLShader LoadGLShader(const GLchar* vs_file, const GLchar* fs_file, std::string name);
	static GLShader GetGLShader(std::string name);

	static Texture LoadTexture(const GLchar* texture_file, GLboolean alpha, std::string name);
	static Texture GetTexture(std::string name);

	static void Clear();

private:
	static GLShader LoadShaderFromFile(const GLchar* vs_file, const GLchar* fs_file);
	static Texture LoadTextureFromFile(const GLchar* texture_file, GLboolean alpha);
};


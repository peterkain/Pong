#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

using std::cout;
using std::endl;

std::map<std::string, GLShader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;
 
GLShader ResourceManager::LoadGLShader(const GLchar* vs_file, const GLchar* fs_file, std::string name) {
	Shaders[name] = LoadShaderFromFile(vs_file, fs_file);
	return Shaders[name];
}

GLShader ResourceManager::GetGLShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar* texture_file, GLboolean alpha, std::string name) {
	Textures[name] = LoadTextureFromFile(texture_file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	for(auto shader : Shaders) {
		glDeleteProgram(shader.second.Program);
	}
	for(auto texture : Textures) {
		glDeleteTextures(1, &texture.second.ID);
	}
}

GLShader ResourceManager::LoadShaderFromFile(const GLchar* vs_file, const GLchar* fs_file) {
	std::string vertexShader;
	std::string fragmentShader;

	try {
		std::ifstream vsFile(vs_file);
		std::ifstream fsFile(fs_file);
		std::stringstream vsStream, fsStream;

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vertexShader = vsStream.str();
		fragmentShader = fsStream.str();
	}
	catch(std::exception e) {
		std::cerr << "Failed to load Shader code for " << vs_file << " and " << fs_file << endl;
	}

	const GLchar* vsCode = vertexShader.c_str();
	const GLchar* fsCode = fragmentShader.c_str();

	GLShader shader;
	shader.Compile(vsCode, fsCode);
	return shader;
}

Texture ResourceManager::LoadTextureFromFile(const GLchar* texture_file, GLboolean alpha) {
	Texture texture;
	if(alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	int width, height;
	unsigned char* image = stbi_load(
		texture_file, &width, &height, 0, STBI_rgb_alpha /*texture.Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb*/
	);

	if(image == nullptr) {
		std::cerr << "Failed to load image " << texture_file << endl;
	}

	texture.Create(width, height, image);
	stbi_image_free(image);

	return texture;
}
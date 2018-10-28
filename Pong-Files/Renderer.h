#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "GLShader.h"

class Renderer
{
public:
	Renderer(GLShader& shader);
	~Renderer();

	void DrawSprite(Texture& texture, glm::vec2 pos, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	GLShader Shader;
	GLuint QuadVAO;

	void InitRenderData();
};


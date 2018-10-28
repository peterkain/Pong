#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(GLShader& shader)
{
	this->Shader = shader;
	this->InitRenderData();
}


Renderer::~Renderer()
{
}

void Renderer::DrawSprite(Texture& texture,
						  glm::vec2 pos,
						  glm::vec2 size,
						  GLfloat rotate,
						  glm::vec3 color)
{
	this->Shader.Use();
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->Shader.SetMat4("model", model, false);
	this->Shader.SetVec3("spriteColor", color, false);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->QuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::InitRenderData() {
	GLuint VBO;
	GLfloat vertices[] = {
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,

		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->QuadVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->QuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

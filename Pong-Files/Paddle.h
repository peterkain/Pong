#pragma once

#include "Object.h"

class Paddle : public Object
{
public:
	Paddle(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation);
	~Paddle();

	void Draw(Renderer& _Renderer);
	virtual void Move(GLfloat dt) = 0;
	virtual void Move(GLfloat dt, GLboolean Keys[]) = 0;

	GLuint Width, Height;
};


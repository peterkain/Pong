#pragma once
#include "Paddle.h"
#include <iostream>

class Player : public Paddle
{
public:
	Player(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation);
	~Player();

	void Move(GLfloat dt);
	void Move(GLfloat dt, GLboolean Keys[]);

	void UpdatePos(glm::vec2 pos) {
		this->Pos = pos;
	}
};


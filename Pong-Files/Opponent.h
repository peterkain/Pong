#pragma once
#include "Paddle.h"

class Opponent : public Paddle
{
public:
	Opponent(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation, glm::vec2 ballPos, glm::vec2 ballSize);
	~Opponent();

	void Move(GLfloat dt);
	void Move(GLfloat dt, GLboolean Keys[]);

	void UpdateBallPos(glm::vec2 newBallPos) {
		this->BallPos = newBallPos;
	}

	void UpdatePos(glm::vec2 pos) {
		this->Pos = pos;
	}

private:
	glm::vec2 BallPos;
	glm::vec2 BallSize;
};


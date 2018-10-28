#include "Opponent.h"
#include <GLFW/glfw3.h>

#include <iostream>

using std::cout;
using std::endl;

#define Log(x) cout << x << endl;

Opponent::Opponent(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation, glm::vec2 ballPos, glm::vec2 ballSize) :
	Paddle(paddleVelocity, paddlePos, paddleSize, width, height, rotation)
{
	UpdateBallPos(ballPos);
	this->BallSize = ballSize;
}


Opponent::~Opponent()
{
}


void Opponent::Move(GLfloat dt, GLboolean Keys[]) {
	if(Keys[GLFW_KEY_UP]) {
		this->Pos.y -= this->Vel.y * dt;
		if(this->Pos.y <= 0) {
			this->Pos.y = 0;
		}
	}
	if(Keys[GLFW_KEY_DOWN]) {
		this->Pos.y += this->Vel.y * dt;
		if(this->Pos.y >= this->Height - this->Size.y) {
			this->Pos.y = this->Height - this->Size.y;
		}
	}
}

void Opponent::Move(GLfloat dt) {
	if(this->BallPos.y + this->BallSize.y > this->Pos.y + this->Size.y / 2 && (this->Size.y + this->Pos.y + (this->Vel.y * dt)) <= this->Height)
		this->Pos.y += this->Vel.y * dt;
	if(this->BallPos.y + this->BallSize.y < this->Pos.y + this->Size.y / 2 && (this->Pos.y + (this->Vel.y * dt)) >= 0)
		this->Pos.y -= this->Vel.y * dt;
}

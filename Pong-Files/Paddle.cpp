#include "Paddle.h"


Paddle::Paddle(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation)
{
	this->Vel = paddleVelocity;
	this->Pos = paddlePos;
	this->Size = paddleSize;
	this->Width = width;
	this->Height = height;
	this->Tex = ResourceManager::GetTexture("paddle");
	this->Rotation = rotation;
}

Paddle::~Paddle()
{
}

void Paddle::Draw(Renderer& _Renderer) {
	_Renderer.DrawSprite(this->Tex, this->Pos, this->Size, this->Rotation);
}

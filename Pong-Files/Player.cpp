#include "Player.h"
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;

#define Log(x) cout << x << endl;

Player::Player(glm::vec2 paddleVelocity, glm::vec2 paddlePos, glm::vec2 paddleSize, GLuint width, GLuint height, GLfloat rotation) :
	Paddle(paddleVelocity, paddlePos, paddleSize, width, height, rotation)
{
}


Player::~Player()
{
}

void Player::Move(GLfloat dt) {

}

void Player::Move(GLfloat dt, GLboolean Keys[]) {
	if(Keys[GLFW_KEY_W]) {
		this->Pos.y -= this->Vel.y * dt;
		if(this->Pos.y <= 0) {
			this->Pos.y = 0;
		}
	}
	if(Keys[GLFW_KEY_S]) {
		this->Pos.y += this->Vel.y * dt;
		if(this->Pos.y >= this->Height - this->Size.y) {
			this->Pos.y = this->Height - this->Size.y;
		}
	}
}

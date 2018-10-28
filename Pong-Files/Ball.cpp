#include "Ball.h"
#include <GLFW/glfw3.h>
#include "Game.h"


Ball::Ball(glm::vec2 ballVelocity, glm::vec2 ballPos, glm::vec2 ballSize, GLuint width, GLuint height, Player* player, Opponent* opponent)
{
	this->Vel = ballVelocity;
	this->ResetVel = ballVelocity;
	this->Pos = ballPos;
	this->StartingPos = ballPos;
	this->Size = ballSize;
	this->Width = width;
	this->Height = height;
	this->Tex = ResourceManager::GetTexture("ball");
	this->_Opponent = opponent;
	this->_Player = player;
	this->Started = false;
	this->Pressed = false;
	this->PlayerPoints = 0;
	this->OpponentPoints = 0;
}


Ball::~Ball()
{
	this->PlayerPoints = 0;
	this->OpponentPoints = 0;
}


void Ball::UpdatePaddlePos(glm::vec2 newPlayerPos, glm::vec2 newOpponentPos) {
	this->_Player->Pos = newPlayerPos;
	this->_Opponent->Pos = newOpponentPos;
}

void Ball::Move(GLfloat dt) {

}

void Ball::Move(GLfloat dt, GLboolean Keys[]) {
	if(Keys[GLFW_KEY_SPACE])
		Started = true;
	if(Started) {
		this->Pos += this->Vel * dt;
		if(this->Pos.y <= 1 || this->Pos.y >= this->Height - this->Size.y - 1) {
			this->Vel.y = -this->Vel.y;
		} if(this->Pos.x <= 0) {
			Reset();
			Started = false;
			OpponentPoints++;
			Game::SetPoints(PlayerPoints, OpponentPoints);
		} if(this->Pos.x >= this->Width - this->Size.x) {
			Reset();
			Started = false;
			PlayerPoints++;
			Game::SetPoints(PlayerPoints, OpponentPoints);
		}
		if(PlayerCollision()) {
			this->Vel.x = abs(this->Vel.x) + 1;
			this->Vel.y += _Player->Size.y - abs((_Player->Pos.y + _Player->Size.y / 2) - this->Pos.y);
		} else if(OpponentCollision()) {
			this->Vel.x = -1 * abs(this->Vel.x) + 1;
			this->Vel.y += _Opponent->Size.y - abs((_Opponent->Pos.y + _Opponent->Size.y / 2) - this->Pos.y);
		}
	}
}

void Ball::Draw(Renderer& _Renderer) {
	_Renderer.DrawSprite(this->Tex, this->Pos, this->Size);
}


bool Ball::PlayerCollision() {
	if((this->Pos.x <= _Player->Pos.x + _Player->Size.x && this->Pos.x >= _Player->Pos.x &&
		this->Pos.y + this->Size.y >= _Player->Pos.y && this->Pos.y <= _Player->Pos.y + _Player->Size.y))
		return true;
	return false;
}

bool Ball::OpponentCollision() {
	if((this->Pos.x >= _Opponent->Pos.x - _Opponent->Size.x && this->Pos.x <= _Opponent->Pos.x &&
		this->Pos.y + this->Size.y >= _Opponent->Pos.y && this->Pos.y <= _Opponent->Pos.y + _Opponent->Size.y))
		return true;
	return false;
}

void Ball::Reset() {
	this->Pos = this->StartingPos;
	Pressed = false;
	Started = false;
	this->Vel = this->ResetVel;
}

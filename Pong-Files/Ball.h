#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "Player.h"
#include "Opponent.h"

class Ball : public Object
{
public:
	Ball(glm::vec2 ballVelocity, glm::vec2 ballPos, glm::vec2 ballSize, GLuint width, GLuint height, Player* player, Opponent* opponent);
	~Ball();

	void Move(GLfloat dt);
	void Move(GLfloat dt, GLboolean Keys[]);
	void Draw(Renderer& _Renderer);
	
	void UpdatePaddlePos(glm::vec2 newPlayerPos, glm::vec2 newOpponentPos);
	void Reset();

	bool Started;
	bool Pressed;

private:
	GLuint Width, Height;
	Player* _Player;
	Opponent* _Opponent;
	glm::vec2 StartingPos;
	glm::vec2 ResetVel;

	bool PlayerCollision();
	bool OpponentCollision();

	int PlayerPoints;
	int OpponentPoints;
};


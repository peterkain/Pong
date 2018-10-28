#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Ball.h"
#include "Paddle.h"
#include "Player.h"
#include "Opponent.h"

enum GameState {
	GAME_ACTIVE,
	GAME_OVER
};

class Game
{
public:
	Game(bool ai);
	~Game();

	void create(GLuint width, GLuint height);
	void init();

	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();

	GLuint width() { return Width; }
	GLuint height() { return Height; }

	static void SetPoints(GLuint playerPoints, GLuint opponentPoints) {
		std::cout << "Player1: " << playerPoints << " | " << "Player2: " << opponentPoints << std::endl;
	}

private:
	GLuint Width, Height;
	glm::vec2 playerPos, opponentPos, ballPos;
	Renderer* _Renderer;
	Ball* _Ball;
	Player* _Player;
	Opponent* _Opponent;

public:
	GameState State;
	GLboolean Keys[1024];
	bool AI;
};


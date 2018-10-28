#include "Game.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

#include "ResourceManager.h"

using std::cout;
using std::endl;

#define FAST_MODE 0
#define Log(x) cout << x << endl

const glm::vec2 PADDLE_SIZE = glm::vec2(16, 64);
const glm::vec2 BALL_SIZE = glm::vec2(15.0f, 15.0f);


#if FAST_MODE
glm::vec2 BALL_VELOCITY = glm::vec2(800.0f, 600.0f);
glm::vec2 PADDLE_VELOCITY = glm::vec2(0.0f, 700.0f); //0, 700
glm::vec2 OPPONENT_VELOCITY = glm::vec2(0.0f, 550.0f);
#else
glm::vec2 BALL_VELOCITY = glm::vec2(408.0f, 303.0f);
glm::vec2 PADDLE_VELOCITY = glm::vec2(0.0f, 350.0f);
glm::vec2 OPPONENT_VELOCITY = glm::vec2(0.0f, 500.0f); //275.0f
#endif

Game::Game(bool ai)
{
	if(!ai) {
		this->AI = false;
		OPPONENT_VELOCITY = PADDLE_VELOCITY;
	} else this->AI = true;

	State = GAME_ACTIVE;
}

Game::~Game() {
	delete _Ball;
	delete _Player;
	delete _Opponent;
	delete _Renderer;
}

void Game::create(GLuint width, GLuint height) {
	this->Width = width;
	this->Height = height;
}

void Game::init() {
	ResourceManager::LoadGLShader("shaders/SpriteTransform.vert", "shaders/SpriteTransform.frag", "shaders");

	glm::mat4 projection = glm::ortho(
		0.0f,
		static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height),
		0.0f,
		-1.0f,
		1.0f
	);

	playerPos = glm::vec2(41, (this->Height / 2 - PADDLE_SIZE.y / 2));
	opponentPos = glm::vec2(this->Width - (41 + PADDLE_SIZE.x), this->Height / 2 - PADDLE_SIZE.y / 2);
	ballPos = glm::vec2(Width / 2 - BALL_SIZE.x / 2, Height / 2 - BALL_SIZE.y / 2);

	ResourceManager::GetGLShader("shaders").Use().SetInt("image", 0);
	ResourceManager::GetGLShader("shaders").SetMat4("projection", projection);

	_Renderer = new Renderer(ResourceManager::GetGLShader("shaders"));
	ResourceManager::LoadTexture("textures/Paddle.jpg", GL_FALSE, "paddle");
	ResourceManager::LoadTexture("textures/Ball.jpg", GL_TRUE, "ball");

	_Player = new Player(PADDLE_VELOCITY, playerPos, PADDLE_SIZE, this->Width, this->Height, 0.0f);
	_Opponent = new Opponent(OPPONENT_VELOCITY, opponentPos, PADDLE_SIZE, this->Width, this->Height, 0.0f, ballPos, BALL_SIZE);
	_Ball = new Ball(BALL_VELOCITY, ballPos, BALL_SIZE, this->Width, this->Height, _Player, _Opponent);
}

void Game::processInput(GLfloat dt) {
	if(this->State == GAME_ACTIVE) {
		_Ball->Move(dt, this->Keys);
		_Player->Move(dt, this->Keys);
	if(this->AI)
		_Opponent->Move(dt);
	else
		_Opponent->Move(dt, this->Keys);
	}
}

void Game::update(GLfloat dt) {
	_Opponent->UpdateBallPos(_Ball->Pos);
	_Ball->UpdatePaddlePos(_Player->Pos, _Opponent->Pos);
	/*_Player->Rotation = -(glfwGetTime() * 4.5);
	_Opponent->Rotation = (glfwGetTime() * 4.5);*/
}

void Game::render() {
	if(this->State == GAME_ACTIVE) {
		_Ball->Draw(*_Renderer);
		_Player->Draw(*_Renderer);
		_Opponent->Draw(*_Renderer);
	}
}

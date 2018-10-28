#pragma once

#include <glm/glm.hpp>
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture.h"

class Object
{
public:
	glm::vec2 Vel;
	glm::vec2 Size;
	glm::vec2 Pos;
	GLfloat Rotation;
	Texture Tex;

public:
	Object();
	~Object();

	virtual void Draw(Renderer& _Renderer) = 0;
	virtual void Move(GLfloat dt) = 0;

};


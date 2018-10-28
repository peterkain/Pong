#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Game.h"
#include "ResourceManager.h"

#define Log(x) cout << x << endl;

using namespace std;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int Width = 800;
int Height = 600;
string Title = "Pong!";

bool ai = true;
Game Pong(ai);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glewInit();

	glGetError();

	glfwSetKeyCallback(window, KeyCallback);

	glViewport(0, 0, Width, Height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Pong.create(Width, Height);
	Pong.init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	while(!glfwWindowShouldClose(window)) {
		GLfloat currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Pong.processInput(deltaTime);
		Pong.update(deltaTime);
		Pong.render();

		glfwSwapBuffers(window);
	}

	ResourceManager::Clear();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if(key >= 0 && key <= 1024) {
		if(action == GLFW_PRESS) {
			Pong.Keys[key] = true;
		} else if(action == GLFW_RELEASE) {
			Pong.Keys[key] = false;
		}
	}
}
#include "Walls.h"

Walls::Walls()
{
		_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0f)), glm::vec3(1.0f, 5.0f, 10.0f));
}

Walls::~Walls()
{

}

void Walls::Draw()
{
	_wallCube.Draw();
}

void Walls::NewWall(int _x)
{
	if (_x == 0)
	{
		_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, -25.0f)), glm::vec3(50.0f, 5.0f, 0.5f));
	}
	else if (_x == 1)
	{
		_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 25.0f)), glm::vec3(50.0f, 5.0f, 0.5f));
	}
	else if (_x == 2)
	{
		_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f, 1.5f, 0.0f)), glm::vec3(0.5f, 5.0f, 50.0f));
	}
	else if (_x == 3)
	{
		_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(25.0f, 1.5f, 0.0f)), glm::vec3(0.5f, 5.0f, 50.0f));
	}
}
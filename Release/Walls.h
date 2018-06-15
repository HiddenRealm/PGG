#ifndef __WALLS__
#define __WALLS__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy


#include "Cube.h"


class Walls
{
public:

	Walls();
	~Walls();

	void Draw();

	void NewWall(int _x);

	glm::mat4 GetModelMatrix() { return _modelMatrix; }

protected:
	int _x = 0;
	glm::mat4 _modelMatrix;

	Cube _wallCube;
};


#endif
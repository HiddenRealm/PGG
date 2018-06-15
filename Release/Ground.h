#ifndef __GROUND__
#define __GROUND__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy


#include "Cube.h"
#include "GameObject.h"


class Ground
{
public:

	Ground();
	~Ground();

	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);
	
	glm::mat4 GetModelMatrix() { return _modelMatrix; }

protected:

	glm::mat4 _modelMatrix;

	glm::vec3 _lightPosition;
	float _turnRate;
	float _speed;
	glm::vec3 _orientation;

	GameObject *_model;

	Cube _groundCube;
};


#endif
#ifndef __PARTICLES__
#define __PARTICLES__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

//Include Libraries 
#include "Cube.h"


class Particles
{
public:
	//Constructer - Deconstructer
	Particles();
	~Particles();

	//Drawing
	void Draw();

	//Update
	void Update();

	//Acclerates the Velocity, as a way of faking the physics
	void VBasicPhys(int _acclX, int _acclY, int _acclZ);

	//Sets the positons of where their start point should be
	void SetPos(glm::vec3 position) { _pos = position; }

	//Sets there velocity
	void SetVel(glm::vec3 velocity) { _vel = velocity; }

	//Checks if they are still active
	bool GetActive() { return active; }

	//Particles Model Matrix
	glm::mat4 GetModelMatrix() { return _modelMatrix; }

protected:
	//Variables
	glm::vec3 _pos;
	glm::vec3 _vel;

	int timer = 0;

	bool active;

	glm::mat4 _modelMatrix;
	glm::mat4 _translationMatrix;
	glm::mat4 _scaleMatrix;

	Cube _particlesCube;
};


#endif
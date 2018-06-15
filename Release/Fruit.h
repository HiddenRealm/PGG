#ifndef __FRUIT__
#define __FRUIT__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy


#include "Cube.h"
#include "Particles.h"
#include "GameObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


class Fruit
{
public:

	Fruit();
	~Fruit();

	bool Update(int value);

	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

	void Rand();

	void Velocity();

	void SetCollected(int value) { _collected = value; }

	int GetSize() { return sparks.size(); }

	glm::vec3 GetPosition1() { return _ran1; }
	glm::vec3 GetPosition2() { return _ran2; }
	glm::vec3 GetPosition3() { return _ran3; }

	glm::mat4 _modelPMatrix;
	glm::mat4 GetModelMatrix() { return _modelMatrix; }
	glm::mat4 GetPModelMatrix();

	std::vector<Particles*> sparks;

protected:
	int _x, _z, _collected = 0;
	int numPars = 0;

	glm::vec3 _pos;
	glm::vec3 _vel;

	glm::vec3 _ran1;
	glm::vec3 _ran2;
	glm::vec3 _ran3;

	glm::vec3 _lightPosition;
	float _turnRate;
	float _speed;
	glm::vec3 _orientation;

	GameObject *_model;

	glm::mat4 _modelMatrix;
	glm::mat4 _translationMatrix;
	glm::mat4 _scaleMatrix;

	Cube _fruitCube;
};


#endif

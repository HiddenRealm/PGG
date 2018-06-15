#ifndef __FRUIT__
#define __FRUIT__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

//Include Libraries 
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
	//Constructer - Deconstructer
	Fruit();
	~Fruit();

	//Update
	bool Update(int value);

	//Drawing
	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

	//Sets the 3 positions of the Fruit
	void Rand();

	//Updates the Velocity of the particles
	void Velocity();

	//sets how many of the fruits have been collected
	void SetCollected(int value) { _collected = value; }

	//gets the size of the particles vector
	int GetSize() { return sparks.size(); }

	//Gets all 3 of the positions the fruit will spawn, for player/vehicle collision
	glm::vec3 GetPosition1() { return _ran1; }
	glm::vec3 GetPosition2() { return _ran2; }
	glm::vec3 GetPosition3() { return _ran3; }

	//Fruit and Particle Martixs
	glm::mat4 _modelPMatrix;
	glm::mat4 GetModelMatrix() { return _modelMatrix; }
	glm::mat4 GetPModelMatrix();

	//Particle Vector
	std::vector<Particles*> sparks;

protected:
	//Variables
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

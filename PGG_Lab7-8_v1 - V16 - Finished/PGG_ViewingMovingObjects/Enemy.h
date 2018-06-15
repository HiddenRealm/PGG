#ifndef __ENEMY__
#define __ENEMY__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

//Include Libraries 
#include "GameObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


class Enemy
{
public:
	//Constructer - Deconstructer
	Enemy();
	~Enemy();

	//This Function picks out the 3 positions that the rock will spawn
	void Rand();

	//Drawing
	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

	//This sends the 3 positions to the Collision detection in vehicle
	glm::vec3 GetPos1() { return _ran1; }
	glm::vec3 GetPos2() { return _ran2; }
	glm::vec3 GetPos3() { return _ran3; }

	//This is how i got around the fact that trying to move this variable resulted in it always eqauling zero
	void SetKills();

	//Update
	bool Update(int kills);

	//Enemy ModelMatrix
	glm::mat4 GetModelMatrix() { return _modelMatrix; }

protected:
	//Variables
	int _x, _z, numPars = 0, _kills;

	glm::vec3 _pos;
	glm::vec3 _vel;

	glm::vec3 _ran1;
	glm::vec3 _ran2;
	glm::vec3 _ran3;

	glm::mat4 _modelMatrix;
	glm::mat4 _translationMatrix;
	glm::mat4 _scaleMatrix;

	glm::vec3 _lightPosition;
	float _turnRate;
	float _speed;
	glm::vec3 _orientation;

	GameObject *_model;
};


#endif
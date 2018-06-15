#ifndef __BULLETS__
#define __BULLETS__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

//Include Libraries 
#include "Cube.h"
#include "Particles.h"
#include "Enemy.h"
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


class Bullets
{
public:

	//Constructer - Deconstructer
	Bullets();
	~Bullets();

	/*Setters to allow me to set the player movement
	 & lets me set the direction that the bullet should travel*/
	void SetPos(glm::vec3 value) { _pos = value; }
	void SetOri(glm::vec3 value1) { _ori = value1; }
	
	//Getter to see how many particles left in the vector
	int GetSize() { return sparks.size(); }

	/*Check if the bullet is still active 
	 or if it should be deleted*/
	bool GetActive() { return active; }

	//Fucntions
	void Draw();
	void Velocity();
	void Update(float deltaTs);

	//Get Bullet position, used for collision
	glm::vec3 GetPos() { return _pos; }

	//Get the Bullets Model Matrix
	glm::mat4 GetModelMatrix() { return _modelMatrix; }

	//Set and Get the particles Model Matrix
	glm::mat4 _modelPMatrix;
	glm::mat4 GetPModelMatrix();

	//Making the Particle Vector
	std::vector<Particles*> sparks;

protected:

	//Variables
	int checking = 0, numPars = 0, timer = 0;
	float _deltaTs;
	bool active;

	glm::vec3 _pos;
	glm::vec3 _nPos;
	glm::vec3 _vel;
	glm::vec3 _ori;
	glm::vec4 _res;
	glm::mat4 _fwd;
	glm::mat4 _translationMatrix;
	glm::mat4 _rotationMatrix;
	glm::mat4 _scaleMatrix;
	glm::mat4 _modelMatrix;

	Cube _bulletCube;
};


#endif

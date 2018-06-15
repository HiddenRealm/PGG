#ifndef __VEHICLE__
#define __VEHICLE__


// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

#include <iostream>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include "Cube.h"
#include "Bullets.h"
#include "Fruit.h"
#include "GameObject.h"
#include "Enemy.h"


class Vehicle
{
public:

	Vehicle();
	~Vehicle();

	void SetTurn( float value ) { _turnRate = value; }

	void SetSpeed( float value ) { _speed = value; }

	int GetSize() { return projectiles.size(); }
	int GetSizes();
	int GetKills() { return kills; }

	bool GetView() { return cView; }

	glm::mat4 GetBModelMatrix(int value);

	int Update( float deltaTs );

	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

	void Movement(SDL_Event evt, float deltaTs);

	bool Wall(bool wall);
	
	bool ECol();

	bool FCol();

	int Counting();
	void Counting2();
	
	glm::mat4 _modelBMatrix;
	glm::mat4 GetModelMatrix() { return _modelMatrix; }
	glm::mat4 GetModelMatrixNoScale() { return _modelMatrixNS; }
	glm::mat4 _modelMatrix, _modelMatrixNS;
	glm::mat4 _fwd;
	glm::vec3 _position;
	glm::vec3 _minP;
	glm::vec3 _maxP;
	glm::vec3 _minF;
	glm::vec3 _maxF;
	glm::vec3 _fruitPos;
	glm::vec3 _minE;
	glm::vec3 _maxE;
	glm::vec3 _enemyPos;
	glm::vec3 _bulletPos;
	
	

	std::vector<Bullets*> projectiles;

protected:
	bool cmdForward = false, cmdBackward = false, cmdTurnRight = false, cmdTurnLeft = false, shooting = false;
	bool forw = true, fruit = false, wall = false, cView = false, hit = false;
	int fruits = 0, checking = 0, bullet = 0, numBuls = 0, timer = 0, amount = 0, counter = 0, numPars = 0, kills = 0;

	glm::vec3 _lightPosition;
	float _turnRate;
	float _speed;
	glm::vec3 _orientation;
	
	GameObject *_model;

	Enemy _enemyObject;
	Fruit _fruitObject;
	Bullets _bulletObject;
	Cube _vehicleCube;
};

#endif

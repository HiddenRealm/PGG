#ifndef __VEHICLE__
#define __VEHICLE__


// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

//Include Libraries 
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
	//Constructer - Deconstructer
	Vehicle();
	~Vehicle();

	//Sets the amount of turnage to change rotation& the Speed the vehicle should go forward
	void SetTurn( float value ) { _turnRate = value; }
	void SetSpeed( float value ) { _speed = value; }

	//Gets Particles Size
	int GetSize() { return projectiles.size(); }
	int GetSizes();
	//Gets the amount of 'Kills' the player has
	int GetKills() { return kills; }

	//Gets what view the player has chosen
	bool GetView() { return cView; }

	//Bullet Model Martix
	glm::mat4 GetBModelMatrix(int value);

	//Update
	int Update( float deltaTs );

	//Drawing
	void Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

	/*Movement, Allows you to move the player 
	& see if bullets have been spawned & Check if view has been changed */
	void Movement(SDL_Event evt, float deltaTs);

	//Checks if the player goes outside the baundry
	bool Wall(bool wall);
	
	//These collsion styles being AABB which i have link inside the bool Wall () function.
	//Player collsion with Enemy
	bool ECol();

	//Player collison with Fruits
	bool FCol();
	
	//Variables
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
	
	//Bullets Vector
	std::vector<Bullets*> projectiles;

protected:
	//Variables
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

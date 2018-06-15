#ifndef __BULLETS__
#define __BULLETS__

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy


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

	Bullets();
	~Bullets();

	void SetPos(glm::vec3 value) { _pos = value; }
	void SetOri(glm::vec3 value1) { _ori = value1; }
	
	int GetSize() { return sparks.size(); }
	bool GetActive() { return active; }

	void Draw();
	void Velocity();

	void Update(float deltaTs);

	glm::vec3 GetPos() { return _pos; }

	glm::mat4 _modelPMatrix;
	glm::mat4 GetModelMatrix() { return _modelMatrix; }
	glm::mat4 GetPModelMatrix();

	std::vector<Particles*> sparks;

protected:

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

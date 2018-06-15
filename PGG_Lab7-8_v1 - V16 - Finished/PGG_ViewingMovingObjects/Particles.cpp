#include "Particles.h"

//Constructer
Particles::Particles()
{
	//set the position and scale
	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f)), glm::vec3(0.05f, 0.05f, 0.05f));
	_scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.05f, 0.05f, 0.05f));

	//make them active
	active = true;
}

//Deconstructer
Particles::~Particles()
{

}

//Drawing
void Particles::Draw()
{
	_particlesCube.Draw();
}


//Update
void Particles::Update()
{
	//Slows the particles way down
	_pos.x += (_vel.x / 100);
	_pos.y += (_vel.y / 75);
	_pos.z += (_vel.z / 100);

	//check if the particles should die yet
	if (timer == 10)
	{
		active = false;
		timer = 0;
	}
	
	//Updates Position
	_translationMatrix = glm::translate(glm::mat4(1), _pos);
	_modelMatrix = _translationMatrix * _scaleMatrix;
	timer++;
}

//Adds the Accelation 
void Particles::VBasicPhys(int _acclX, int _acclY, int _acclZ)
{
	_vel.x += _acclX / 2;
	_vel.y += _acclY / 2;
	_vel.z += _acclZ / 2;
}


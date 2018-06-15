#include "Bullets.h"

//Constructer
Bullets::Bullets()
{
	srand(time(NULL));
	active = true;
	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(_pos.x, -0.15f, _pos.z)), glm::vec3(0.15f, 0.15f, 0.2f));
}

//Deconstructer
Bullets::~Bullets()
{

}

//Drawing
void Bullets::Draw()
{
	_bulletCube.Draw();
}

/*
nPos is being set to the position of the vehicle so that it can be sent to the 
particles without risking changing the variable, The rotation code under that is the same from vehicle
it rotates the vehicle around depending how much it has been turnt, allowing it to always be facing forward
took me a bit to full understand what was going on here
*/
void Bullets::Update(float deltaTs)
{
	_nPos = _pos;
	if (active == true)
	{
		_pos.y = -0.15f;
		_rotationMatrix = glm::rotate(glm::mat4(1.0f), _ori.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_fwd = glm::rotate(glm::mat4(1.0f), _ori.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_fwd = glm::translate(_fwd, glm::vec3(0.0f, 0.0f, -1.0f));
		_res = _fwd * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		_pos += glm::vec3(_res) * 20.0f * deltaTs;

		//Set the Scale, Translation and Rotation Matrix's so i could set the Model Matrix
		_scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.15f, 0.15f, 0.20f));

		_translationMatrix = glm::translate(glm::mat4(1), _pos);

		_modelMatrix = _translationMatrix * _rotationMatrix * _scaleMatrix;
	}
	//If statement to check if the bullet has gone past the walls
	if (_pos.x >= 25 || _pos.x <= -25 || 
		_pos.z >= 25 || _pos.z <= -25)
	{
		timer++;

		//the timer is to make sure it only spawns 1 set of particles
		if (timer == 1)
		{
			//My Particle Spawning system
			for (int x = 0; x < 100; x++)
			{
				sparks.push_back(new Particles());
				sparks[x]->SetPos(_nPos);
				Velocity();
				sparks[x]->SetVel(_vel);
			}
		}
	}

	//Updates all of my BulletParticles & Adds Basic Physics to them
	//Also Checks if they are still active
	for (int x = 0; x < sparks.size(); x++)
	{
		sparks[x]->Update();
		sparks[x]->VBasicPhys(0, 1, 0);

		if (sparks[x]->GetActive() == false)
		{
			sparks.erase(sparks.begin() + x);
		}
	}
	
	//It delays when the bullet dies so that it can
	//give it enough time to spawn and run the 'Animation'
	//of the particles
	if (timer == 11)
	{
		active = false;
	}
}

//makes a random velocity
void Bullets::Velocity()
{
	_vel.x = rand() % 10;
	_vel.y = rand() % 10;
	_vel.z = rand() % 10;

	_vel.x = _vel.x - 5;
	_vel.y = _vel.y - 5;
	_vel.z = _vel.z - 5;
}

//Gets and return the Model Matrix for each individual Particle
glm::mat4 Bullets::GetPModelMatrix()
{
	if (numPars < sparks.size())
	{
		_modelPMatrix = sparks[numPars]->GetModelMatrix();
		sparks[numPars]->Draw();
		numPars++;
	}

	if (numPars >= sparks.size())
	{
		numPars = 0;
	}

	return _modelPMatrix;
}


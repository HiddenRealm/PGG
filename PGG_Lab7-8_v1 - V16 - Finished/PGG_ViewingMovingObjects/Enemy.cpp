#include "Enemy.h"

//Constructer
Enemy::Enemy()
{
	srand(time(NULL));
	//Picks the 3 Locations of spawn
	Rand();

	//sets pos to the first location
	_pos = _ran1;
	_kills = 0;

	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,  0.0f, 0.0f)), glm::vec3(0.8f, 0.8f, 0.8f));

	//Sets the light Position, i know this is only meant to be made once but 
	// i didnt want to have to keep feeding it though, 
	//this is one of the reason i wish i made a game manager
	_lightPosition = glm::vec3(0, 10, 0);

	//makes a new instance of GameObject
	_model = new GameObject();

	//Makes a new instance of Material
	Material *modelMaterial = new Material();

	//loads the shaders to the material
	modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	//changes the overall colour of the texture
	modelMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	//sets the material to be the bmp that is sent in
	modelMaterial->SetTexture("Enemy.bmp");
	//sets the light position, so it can work out the light maths i assume
	modelMaterial->SetLightPosition(_lightPosition);
	//Applies the material to the model
	_model->SetMaterial(modelMaterial);

	//makes a new instance of mesh
	Mesh *modelMesh = new Mesh();
	//loads the obj into the mesh code
	modelMesh->LoadOBJ("Cube.obj");
	//sets the model to have this new mesh, also apply the material onto it now
	_model->SetMesh(modelMesh);

	//model set position & scale
	_model->SetPosition(_pos.x, _pos.y, _pos.z);
	_model->SetScale(0.8f, 0.8f, 0.8f);
}

//Deconstructer
Enemy::~Enemy()
{

}

//Drawing
void Enemy::Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
{
	_model->Draw(_viewMatrix, _projMatrix);
}

//Just Adds one to kills
void Enemy::SetKills()
{ 
	_kills++;
}

//Updates
bool Enemy::Update(int kills)
{
	_kills = kills;
	if (_kills == 1)
	{
		_pos = _ran2;
	}
	else if (_kills == 2)
	{
		_pos = _ran3;
	}
	else if (_kills == 3)
	{
		_pos = { 0.0f, -1.0f, 0.0f };
		return true;
	}

	_scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.8f, 0.8f, 0.8f));

	_translationMatrix = glm::translate(glm::mat4(1), _pos);

	_modelMatrix = _translationMatrix * _scaleMatrix;

	_model->SetPosition(_pos.x, _pos.y, _pos.z);
}

//Picks random numbers between (-24) - (24)
void Enemy::Rand()
{
	for (int e = 0; e < 3; e++)
	{
		_x = rand() % 24;
		_z = rand() % 24;

		if (rand() % 2 == 0)
		{
			_x = -_x;
		}
		if (rand() % 2 == 0)
		{
			_z = -_z;
		}

		if (e == 0)
		{
			_ran1.x = _x;
			_ran1.z = _z;
		}
		else if (e == 1)
		{
			_ran2.x = _x;
			_ran2.z = _z;
		}
		else if (e == 2)
		{
			_ran3.x = _x;
			_ran3.z = _z;
		}
	}
}
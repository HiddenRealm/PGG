#pragma comment(lib, "winmm.lib")

#include "Enemy.h"

Enemy::Enemy()
{
	srand(time(NULL));
	Rand();

	_pos = _ran1;
	_kills = 0;

	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,  0.0f, 0.0f)), glm::vec3(0.8f, 0.8f, 0.8f));

	_lightPosition = glm::vec3(0, 10, 0);

	_model = new GameObject();

	Material *modelMaterial = new Material();

	modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	modelMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	modelMaterial->SetTexture("Enemy.bmp");
	modelMaterial->SetLightPosition(_lightPosition);
	_model->SetMaterial(modelMaterial);

	Mesh *modelMesh = new Mesh();
	modelMesh->LoadOBJ("Cube.obj");
	_model->SetMesh(modelMesh);

	_model->SetPosition(_pos.x, _pos.y, _pos.z);
	_model->SetScale(0.8f, 0.8f, 0.8f);
}

Enemy::~Enemy()
{

}

void Enemy::Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
{
	_model->Draw(_viewMatrix, _projMatrix);
}

void Enemy::SetKills()
{ 
	_kills++;
}

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
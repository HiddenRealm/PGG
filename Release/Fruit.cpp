#pragma comment(lib, "winmm.lib")

#include "Fruit.h"

Fruit::Fruit()
{
	srand(time(NULL));
	Rand();

	_pos = _ran1;

	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.4f, 0.0f)), glm::vec3(0.4f, 0.4f, 0.4f));

	_lightPosition = glm::vec3(0, 10, 0);

	_model = new GameObject();

	Material *modelMaterial = new Material();

	modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	modelMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 0.0));
	modelMaterial->SetTexture("Fruit.bmp");
	modelMaterial->SetLightPosition(_lightPosition);
	_model->SetMaterial(modelMaterial);

	Mesh *modelMesh = new Mesh();
	modelMesh->LoadOBJ("Cube.obj");
	_model->SetMesh(modelMesh);

	_model->SetPosition(0.0f, -0.4f, 0.0f);
	_model->SetScale(0.4f, 0.4f, 0.4f);
}

Fruit::~Fruit()
{

}

bool Fruit::Update(int value)
{
	_collected = value;
	
	if (_collected == 1)
	{
		for (int x = 0; x < 100; x++)
		{
			sparks.push_back(new Particles());
			sparks[x]->SetPos(_pos);
			Velocity();
			sparks[x]->SetVel(_vel);
		}
		
		PlaySound(TEXT("Collected.wav"), NULL, SND_FILENAME && SND_ASYNC);
		_pos = _ran2;
	}
	else if (_collected == 2)
	{
		for (int x = 0; x < 100; x++)
		{
			sparks.push_back(new Particles());
			sparks[x]->SetPos(_pos);
			Velocity();
			sparks[x]->SetVel(_vel);
		}

		PlaySound(TEXT("Collected.wav"), NULL, SND_FILENAME && SND_ASYNC);
		_pos = _ran3;
	}
	else if (_collected == 3)
	{
		PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME && SND_ASYNC);
		_pos = { 0.0f, -1.0f, 0.0f };
		return false;
	}

	_scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.4f, 0.4f, 0.4f));

	_translationMatrix = glm::translate(glm::mat4(1), _pos);

	_modelMatrix = _translationMatrix * _scaleMatrix;
	 
	_model->SetPosition(_pos.x, _pos.y, _pos.z);

	for (int x = 0; x < sparks.size(); x++)
	{
		sparks[x]->Update();
		sparks[x]->VBasicPhys(0,1,0);
		
		if (sparks[x]->GetActive() == false)
		{
			sparks.erase(sparks.begin() + x);
		}
	}

	return true;
}

void Fruit::Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
{
	_model->Draw(_viewMatrix, _projMatrix);
}

glm::mat4 Fruit::GetPModelMatrix()
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

void Fruit::Rand()
{
	for (int e = 0; e < 3; e++)
	{
		_x = ((rand() % 48) - 24);
		_z = ((rand() % 48) - 24);

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

void Fruit::Velocity() 
{
	_vel.x = rand() % 10;
	_vel.y = rand() % 10;
	_vel.z = rand() % 10;

	_vel.x = _vel.x - 5;
	_vel.y = _vel.y - 5;
	_vel.z = _vel.z - 5;
}
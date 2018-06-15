#include "Vehicle.h"


Vehicle::Vehicle()
{
	// Initial orientation is facing negative z
	_orientation = glm::vec3( 0, 0, -1 );
	_speed = 0.0f;
	_turnRate = 0.0f;
	int bulMove = SDL_GetTicks();

	_lightPosition = glm::vec3(10, 10, 0);

	_model = new GameObject();

	Material *modelMaterial = new Material();

	modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	modelMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	modelMaterial->SetTexture("Player.bmp");
	modelMaterial->SetLightPosition(_lightPosition);
	_model->SetMaterial(modelMaterial);

	Mesh *modelMesh = new Mesh();
	modelMesh->LoadOBJ("Cube.obj");
	_model->SetMesh(modelMesh);

	_model->SetScale(0.5f, 0.5f, 1.0f);
}

Vehicle::~Vehicle()
{

}

int Vehicle::Update( float deltaTs )
{
	// Update the orientation:
	// Build a rotation matrix using the _turnRate * _speed as the rotation amount and y-up as the axis of rotation
	// Multiply this matrix by the previous orientation to rotate the orientation vector
	// Normalise the resulting vector to reduce rounding errors - it's important this is a unit vector

    _orientation.x += _turnRate * deltaTs;
	_orientation.y += _turnRate * deltaTs;

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), _orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));

	_fwd = glm::rotate(glm::mat4(1.0f), _orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	_fwd = glm::translate(_fwd, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 res = _fwd * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	_position += glm::vec3(res) * _speed * deltaTs;


	// Update the position
	// the _orientation is a unit vector, so need to use the current _speed as the magnitude
	_minP = { _position.x - 0.25f, 0.0f, _position.z - 0.5f };
	_maxP = { _position.x + 0.25f, 0.0f, _position.z + 0.5f };

	// Create the rotation matrix based on the current orientation
	glm::vec3 upDirection( 0, 1, 0 );
	glm::vec3 rightDirection( 1, 0, 0 );/* = write code here ;*/
//	glm::mat4 rotationMatrix = glm::mat4( glm::vec4(_orientation,0.0f), glm::vec4(upDirection,0.0f), glm::vec4(rightDirection,0.0f), glm::vec4(0,0,0,1) );

	// Scale matrix for the vehicle
	glm::mat4 scaleMatrix = glm::scale( glm::mat4( 1 ), glm::vec3( 0.5f, 0.5f, 1.0f ));
	// Translation matrix based on current position
	glm::mat4 translationMatrix = glm::translate(  glm::mat4(1), _position );

	// Update model matrix by first scaling, then rotating, then translating
	_modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	// Keep a version of this without the scale - useful for camera transforms
	_modelMatrixNS = translationMatrix * rotationMatrix;

	fruit = FCol();

	hit = ECol();

	Counting2();

	_model->SetRotation(_orientation.x, _orientation.y, _orientation.z);
	_model->SetPosition(_position.x, _position.y, _position.z);

	for (int x = 0; x < projectiles.size(); x++)
	{
		projectiles[x]->Update(deltaTs);
		_bulletPos = projectiles[x]->GetPos();

		if (projectiles[x]->GetActive() == false)
		{
			projectiles.erase(projectiles.begin() + x );
			bullet--;
		}
	}

	counter++;
	int x;
	return x = Counting();
}

void Vehicle::Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
{
		_model->SetPosition(_position.x, _position.y, _position.z);

		_model->Draw(_viewMatrix, _projMatrix);
}

int Vehicle::GetSizes()
{
	int x = 0;

	for (int c = 0; c < projectiles.size(); c++)
	{
		x += projectiles[c]->GetSize();
	}

	return x;
}

glm::mat4 Vehicle::GetBModelMatrix(int value)
{
	if (value == 1)
	{
		if (numBuls < projectiles.size())
		{
			_modelBMatrix = projectiles[numBuls]->GetModelMatrix();
			projectiles[numBuls]->Draw();
			numBuls++;
		}

		if (numBuls >= projectiles.size())
		{
			numBuls = 0;
		}

		return _modelBMatrix;
	}
	else if (value == 2)
	{
		bool check = true;
		if (numBuls < projectiles.size())
		{
			if (numPars < projectiles[numBuls]->GetSize())
			{
				_modelBMatrix = projectiles[numBuls]->GetPModelMatrix();
				numPars++;
				check = false;
				if (numPars >= projectiles[numBuls]->GetSize())
				{
					numBuls++;
				}
			}
		}

		if (numBuls >= projectiles.size() || check == false)
		{
			numBuls = 0;
			numPars = 0;
		}


		return _modelBMatrix;
	}
}

void Vehicle::Movement(SDL_Event evt, float deltaTs)
{
	if (evt.type == SDL_KEYDOWN)
	{
		// The event type is SDL_KEYDOWN
		// This means that the user has pressed a key
		// Let's figure out which key they pressed
		switch (evt.key.keysym.sym)
		{
			case SDLK_a: { cmdTurnLeft = true; break; }
			case SDLK_d: { cmdTurnRight = true; break; }
			case SDLK_w: { cmdForward = true; break; }
			case SDLK_s: {cmdBackward = true; break; }
			case SDLK_SPACE: {shooting = true; break; }
			case SDLK_v:
			{
				if (counter >= amount)
				{
					amount = 100;
					cView = !cView;
				}
				break;
			}
		}
	}

	if (evt.type == SDL_KEYUP)
	{
		// The event type is SDL_KEYDOWN
		// This means that the user has pressed a key
		// Let's figure out which key they pressed
		switch (evt.key.keysym.sym)
		{
		case SDLK_a: { cmdTurnLeft = false; break; }
		case SDLK_d: { cmdTurnRight = false; break; }
		case SDLK_w: { cmdForward = false; break; }
		case SDLK_s: { cmdBackward = false; break; }
		case SDLK_SPACE: {shooting = false; break; }
		}
	}

	if (shooting == true)
	{
		if (projectiles.size() <= 20)
		{
			projectiles.push_back(new Bullets());
			projectiles[bullet]->SetPos(_position);
			projectiles[bullet]->SetOri(_orientation);
			bullet++;
		}
	}

	if (cmdForward && !cmdBackward)
	{
		wall = Wall(wall);
		if (wall == false)
		{
			SetSpeed(-10.0f);
		}
		else
		{
			SetSpeed(0.0f);
			PlaySound(TEXT("Fail.wav"), NULL, SND_FILENAME && SND_ASYNC);
			_position = { 0.0f, 0.0f, 0.0f };
		}
	
	}
	else if (cmdBackward && !cmdForward)
	{
		SetSpeed(10.0f);
	}
	else
	{
		SetSpeed(0.0f);
	}

	if (cmdTurnRight && !cmdTurnLeft)
	{
		SetTurn(-1.0f);
		/*rotation += (-1 * deltaTs);*/
	}
	else if (cmdTurnLeft && !cmdTurnRight)
	{
		SetTurn(1.0f);
		//rotation += (1 * deltaTs);
	}
	else
	{
		SetTurn(0.0f);
	}
}

bool Vehicle::Wall(bool wall)
{
	if ((_position.x + 1.5f) >= 24.5 || (_position.x - 1.0f) <= -24.5 || 
		(_position.z + 1.0f) >= 24.5 || (_position.z - 1.0f) <= -24.5)
	{
		wall = true;
	}
	else
	{
		wall = false;
	}

	return wall;

	/*
	Collision later on:
	https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
	https://rdmilligan.wordpress.com/2016/12/28/3d-collision-detection-with-c/
	These should detect if two things touch each other, 
	would be good good for;
	-Player Vs. Enemy
	-Player Vs. Bullet
	-Player Vs. Apple
	-Enemy Vs. Bullet
	Could use the basic Collision i have here for Bullet Vs. Wall


	glm::vec3 _cubeMin1 = {25.0f, 0.0f, -24.75f};
	glm::vec3 _cubeMax1 = { -25.0f, 0.0f, -25.25f };
	*/
}

bool Vehicle::FCol()
{
	if (fruits == 0)
	{
		_fruitPos = _fruitObject.GetPosition1();
		_minF = { _fruitPos.x - 0.2f, _fruitPos.y, _fruitPos.z - 0.2f };
		_maxF = { _fruitPos.x + 0.2f, _fruitPos.y, _fruitPos.z + 0.2f };
	}
	else if (fruits == 1)
	{
		_fruitPos = _fruitObject.GetPosition2();
		_minF = { _fruitPos.x - 0.2f, _fruitPos.y, _fruitPos.z - 0.2f };
		_maxF = { _fruitPos.x + 0.2f, _fruitPos.y, _fruitPos.z + 0.2f };

	}
	else if (fruits == 2)
	{
		_fruitPos = _fruitObject.GetPosition3();
		_minF = { _fruitPos.x - 0.2f, _fruitPos.y, _fruitPos.z - 0.2f };
		_maxF = { _fruitPos.x + 0.2f, _fruitPos.y, _fruitPos.z + 0.2f };
	}
	
	return (_minP.x <= _maxF.x && _maxP.x >= _minF.x) &&
		   (_minP.z <= _maxF.z && _maxP.z >= _minF.z);
}

bool Vehicle::ECol()
{

	if (kills == 0)
	{
		_enemyPos = _enemyObject.GetPos1();
		_minE = { _enemyPos.x - 0.4f, _enemyPos.y, _enemyPos.z - 0.4f };
		_maxE = { _enemyPos.x + 0.4f, _enemyPos.y, _enemyPos.z + 0.4f };
	}
	else if (kills == 1)
	{
		_enemyPos = _enemyObject.GetPos2();
		_minE = { _enemyPos.x - 0.4f, _enemyPos.y, _enemyPos.z - 0.4f };
		_maxE = { _enemyPos.x + 0.4f, _enemyPos.y, _enemyPos.z + 0.4f };
	}
	else if (kills == 2)
	{
		_enemyPos = _enemyObject.GetPos3();
		_minE = { _enemyPos.x - 0.4f, _enemyPos.y, _enemyPos.z - 0.4f };
		_maxE = { _enemyPos.x + 0.4f, _enemyPos.y, _enemyPos.z + 0.4f };
	}

	return (_minP.x <= _maxE.x && _maxP.x >= _minE.x) &&
		   (_minP.z <= _maxE.z && _maxP.z >= _minE.z);
}

int Vehicle::Counting()
{
	if (fruit == true)
	{
		if (counter > timer)
		{
			if (fruits == 0)
			{
				fruits++;
				timer == 300;
				return 1;
			}
			else if (fruits == 1)
			{
				fruits++;
				return 2;
			}
			else if (fruits == 2)
			{
				fruits++;
				return 3;
			}
			else
			{
				return 0;
			}
			counter = 0;
		}
	}
}

void Vehicle::Counting2()
{
	if (hit == true)
	{
		if (counter > timer)
		{
			if (kills == 0)
			{
				kills++;
				timer == 300;
			}
			else if (kills == 1)
			{
				kills++;
			}
			else if (kills == 2)
			{
				kills++;
			}
			counter = 0;
		}
	}
	
}
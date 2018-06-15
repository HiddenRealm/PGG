#include "Scene.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constructer
Scene::Scene()
{
	srand(time(NULL));

	_cameraAngleX = 0.5f, _cameraAngleY = 0.0f;

	_shaderModelMatLocation = 0;
	_shaderViewMatLocation = 0;
	_shaderProjMatLocation = 0;

	_shaderDiffuseColLocation = 0;
	_shaderEmissiveColLocation = 0;
	_shaderWSLightPosLocation = 0;


	BuildShaders();
	
	// Set up the viewing matrix
	// This represents the camera's orientation and position
	//_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );
	

	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
}

//Deconstructer
Scene::~Scene()
{
}

//Update
bool Scene::Update( float deltaTs )
{
	//win = how many fruit collected
	//end1  = is the first win condition
	//end2 = is the second win condition
	win = _vehicleObject.Update( deltaTs );
	end1 = _fruitObject.Update(win);
	//Checks how many rocks 'Killed'
	int kills = _vehicleObject.GetKills();
	end2 = _enemyObject.Update(kills);

	//Checks if the Game is won
	if (end1 == false && end2 == true)
	{
		SDL_Delay(5000);
		return false;
	}

	//This checks what camera is mounted (first or third person)
	cView = _vehicleObject.GetView();

	//Picks where the camera should be mounted
	if (cView == false)
	{
		_viewMatrix = _vehicleObject._modelMatrixNS;
		_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 1, 0));
		_viewMatrix = glm::translate(_viewMatrix, glm::vec3(0, 1, 5));
		_viewMatrix = glm::inverse(_viewMatrix);
	}
	else if (cView == true)
	{
		_viewMatrix = _vehicleObject._modelMatrixNS;
		_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 0.25, 0));
		_viewMatrix = glm::translate(_viewMatrix, glm::vec3(0, 0, -0.5));
		_viewMatrix = glm::inverse(_viewMatrix);
	}

	return true;
}

//Drawing
void Scene::Draw()
{
		// Activate the shader program
	glUseProgram( _shaderProgram );

		glUniform3f( _shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f );
		glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix) );
		glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(_projMatrix) );
		glUniform4f( _shaderWSLightPosLocation,  1,2,1,1);
	
		// Draw the ground
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr( _groundObject.GetModelMatrix() ) );
		glUniform3f( _shaderDiffuseColLocation, 0.9f, 0.9f, 0.3f );
			_groundObject.Draw(_viewMatrix, _projMatrix);
		
			//Draws 4 of them (walls)
		for (int x = 0; x < 4; x++)
		{
			// Draw the walls
			glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_wallObject.GetModelMatrix()));
			glUniform3f(_shaderDiffuseColLocation, 0.6f, 0.3f, 0.3f);
			_wallObject.Draw();
			_wallObject.NewWall(x);
		}

		//Draw Fruit
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_fruitObject.GetModelMatrix()));
		glUniform3f(_shaderDiffuseColLocation, 1.0f, 0.0f, 0.0f);
		glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);
			_fruitObject.Draw(_viewMatrix, _projMatrix);

		// Draw the vehicle
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr( _vehicleObject.GetModelMatrix()) );
		glUniform3f( _shaderDiffuseColLocation, 1.0f, 1.0f, 1.0f );
		glUniform3f( _shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f );
			_vehicleObject.Draw(_viewMatrix, _projMatrix);

		// Draw the bullets
		for (int x = 0; x < _vehicleObject.GetSize(); x++)
		{
			glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_vehicleObject.GetBModelMatrix(1)));
			glUniform3f(_shaderDiffuseColLocation, 0.0f, 1.0f, 0.0f);
			glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);
		}

		//Draw Player -> Fruit Particles
		for (int z = 0; z < _fruitObject.GetSize(); z++)
		{
			MakeColour();
			glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_fruitObject.GetPModelMatrix()));
			glUniform3f(_shaderDiffuseColLocation, _red, _green, _blue);
			glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);
		}

		//Draw Bullet -> Wall Particles (Bullets * Particles)
		//Every bullet can have 100 particles (max particles 2000)
		int buls = _vehicleObject.GetSize();
		int pars = _vehicleObject.GetSizes();
		for (int c = 0; c < (buls * pars); c++)
		{
			glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_vehicleObject.GetBModelMatrix(2)));
			glUniform3f(_shaderDiffuseColLocation, 1.0f, 0.0f, 1.0f);
			glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);
		}

		// Draw the enemy
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_enemyObject.GetModelMatrix()));
		glUniform3f(_shaderDiffuseColLocation, 1.0f, 1.0f, 1.0f);
		glUniform3f(_shaderEmissiveColLocation, 0.0f, 0.0f, 0.0f);
		_enemyObject.Draw(_viewMatrix, _projMatrix);

	glUseProgram( 0 );
}

//Shader Code (compile then checks to make sure a texture has been loaded)
bool Scene::CheckShaderCompiled( GLint shader )
{
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;

		return false;
	}
	return true;
}

//builds the shaders
void Scene::BuildShaders()
{
	// OpenGL doesn't provide any functions for loading shaders from file
	// I'm feeling lazy, so just hardcoding them here
	
	// This is the vertex shader
	const GLchar *vShaderText = "#version 430 core\n\
						 layout(location = 0) in vec4 vPosition;\n\
						 layout(location = 1) in vec3 vNormalIn;\n\
						 \n\
						 uniform mat4 modelMat;\n\
						 uniform mat4 invModelMat;\n\
						 uniform mat4 viewMat;\n\
						 uniform mat4 projMat;\n\
						 \n\
						 uniform vec4 worldSpaceLightPos = {1,0.0,1,1};\n\
						 \n\
						 out vec3 vNormalV;\n\
						 out vec3 eyeSpaceLightPosV;\n\
						 out vec3 eyeSpaceVertPosV;\n\
						 \n\
						 void main()\n\
						 {\n\
								gl_Position = projMat * viewMat * modelMat * vPosition;\n\
								\n\
								eyeSpaceVertPosV = vec3(viewMat * modelMat * vPosition);\n\
								eyeSpaceLightPosV = vec3(viewMat * worldSpaceLightPos);\n\
								\n\
								vNormalV = mat3(viewMat * modelMat) * vNormalIn;\n\
						 }";

	// This is the fragment shader
	const GLchar *fShaderText = "#version 430 core\n\
								in vec3 vNormalV;\n\
								in vec3 eyeSpaceLightPosV;\n\
								in vec3 eyeSpaceVertPosV;\n\
								\n\
								uniform vec3 lightColour = {1,1,1};\n\
								uniform vec3 emissiveColour = {0,0,0};\n\
								uniform vec3 ambientColour  = {0.1f,0.1f,0.2f};\n\
								uniform vec3 diffuseColour  = {0.1f,0.1f,0.1f};\n\
								uniform vec3 specularColour = {0.0f,1.0f,0.0f};\n\
								uniform float shininess     = 50.0f;\n\
								uniform float alpha         = 1.0f;\n\
								\n\
								out vec4 fragColour;\n\
								\n\
								void main()\n\
								{\n\
									vec3 lightDir = normalize( eyeSpaceLightPosV - eyeSpaceVertPosV );\n\
									vec3 normal = normalize( vNormalV );\n\
									vec3 eyeDir = normalize( -eyeSpaceVertPosV );\n\
									vec3 halfVec = normalize( eyeDir + lightDir );\n\
									\n\
										vec3 diffuse = diffuseColour * lightColour * max( dot( normal, lightDir ), 0);\n\
										\n\
										vec3 specular = vec3(0);\n\
										\n\
										fragColour = vec4( emissiveColour + ambientColour + diffuse + specular, alpha);\n\
								}";

	// The 'program' stores the shaders
	_shaderProgram = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	// Give GL the source for it
	glShaderSource( vShader, 1, &vShaderText, NULL );
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( !CheckShaderCompiled( vShader ) )
	{
		std::cerr<<"ERROR: failed to compile vertex shader"<<std::endl;
		return;
	}
	// This links the shader to the program
	glAttachShader( _shaderProgram, vShader );

	// Same for the fragment shader
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fShader, 1, &fShaderText, NULL );
	glCompileShader( fShader );
	if( !CheckShaderCompiled( fShader ) )
	{
		std::cerr<<"ERROR: failed to compile fragment shader"<<std::endl;
		return;
	}
	glAttachShader( _shaderProgram, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( _shaderProgram );
	// Check this worked
	GLint linked;
	glGetProgramiv( _shaderProgram, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( _shaderProgram, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( _shaderProgram, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return;
	}


	// We will define matrices which we will send to the shader
	// To do this we need to retrieve the locations of the shader's matrix uniform variables
	glUseProgram( _shaderProgram );
	_shaderModelMatLocation = glGetUniformLocation( _shaderProgram, "modelMat" );
	_shaderViewMatLocation = glGetUniformLocation( _shaderProgram, "viewMat" );
	_shaderProjMatLocation = glGetUniformLocation( _shaderProgram, "projMat" );
	
	_shaderDiffuseColLocation = glGetUniformLocation( _shaderProgram, "diffuseColour" );
	_shaderEmissiveColLocation = glGetUniformLocation( _shaderProgram, "emissiveColour" );
	_shaderWSLightPosLocation = glGetUniformLocation( _shaderProgram, "worldSpaceLightPos" );
}

//Makes randoms floats (set these to R,G & B)
void Scene::MakeColour()
{
	_red = rand() % 100 + 1;
	_green = rand() % 100 + 1;
	_blue = rand() % 100 + 1;

	_red = _red / 100;
	_green = _green / 100;
	_blue = _blue / 100;
}

#include "Ground.h"
#include "Vehicle.h"
#include "Walls.h"
#include "Fruit.h"
#include "Bullets.h"
#include "Enemy.h"

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy

class Scene
{
public:

	Scene();
	~Scene();

	void SetTurn( float value ) { _vehicleObject.SetTurn( value ); }
	void SetSpeed( float value ) { _vehicleObject.SetSpeed( value ); }
	
	void Movement(SDL_Event evt, float deltaTs) { _vehicleObject.Movement(evt, deltaTs); }

	void ChangeCameraAngleX( float value ) { _cameraAngleX += value; }
	void ChangeCameraAngleY( float value ) { _cameraAngleY += value; }

	bool Update( float deltaTs );
	
	void MakeColour();

	void Draw();


protected:

	Ground _groundObject;
	Vehicle _vehicleObject;
	Walls _wallObject;
	Fruit _fruitObject;
	Bullets _bulletObject;
	Enemy _enemyObject;

	float _red = 0, _green = 0, _blue = 0;

	int win = 0;
	bool end1 = false;
	bool end2 = false;
	bool cView;

	glm::mat4 _viewMatrix;
	
	// Set up a projection matrix
	glm::mat4 _projMatrix;
	// Angle of rotation for our camera
	float _cameraAngleX, _cameraAngleY;


	// TODO: Exercise: extract all shader code and put it in its own class

	GLuint _shaderProgram;

	int _shaderModelMatLocation;
	int _shaderViewMatLocation;
	int _shaderProjMatLocation;

	int _shaderDiffuseColLocation, _shaderEmissiveColLocation;
	int _shaderWSLightPosLocation;

	bool CheckShaderCompiled( GLint shader );
	void BuildShaders();

};

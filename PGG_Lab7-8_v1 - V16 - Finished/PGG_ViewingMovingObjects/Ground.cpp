
#include "Ground.h"

//Constructer
Ground::Ground()
{
	_modelMatrix = glm::scale( glm::translate( glm::mat4( 1.0f ), glm::vec3( 0.0f, -0.5f, 0.0f ) ), glm::vec3( 50.0f, 0.1f, 50.0f ) );

	_lightPosition = glm::vec3(0, 10, 0);

	_model = new GameObject();

	Material *modelMaterial = new Material();

	modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	modelMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	modelMaterial->SetTexture("Floor.bmp");
	modelMaterial->SetLightPosition(_lightPosition);
	_model->SetMaterial(modelMaterial);

	Mesh *modelMesh = new Mesh();
	modelMesh->LoadOBJ("Cube.obj");
	_model->SetMesh(modelMesh);

	_model->SetPosition(0.0f, -0.5f, 0.0f);
	_model->SetScale(50.0f, 0.1f, 50.0f);
}

//Deconstructer
Ground::~Ground()
{

}

//Drawing
void Ground::Draw(glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
{
	_model->Draw(_viewMatrix, _projMatrix);
}


#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "UIManager.h"
#include "OutlineGizmo.h"
#include "MergedActor.h"
#include <iostream>
#include "Cube.h"
#include "PhysicsComponent.h"
#include "Plane.h"
#include "Sphere.h"
#include "Mesh.h"
#include "MeshObject.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::initialize(void* shader_byte_code, size_t size_shader)
{
	width = UIManager::WINDOW_WIDTH;
	height = UIManager::WINDOW_HEIGHT;
	this->shader_byte_code = shader_byte_code;
	this->size_shader = size_shader;
}

void GameObjectManager::createCube()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Cube* cube = new Cube("Cube", shader_byte_code, size_shader);
	cube->setRigidBodyEnabled(true);
	objList.push_back(cube);
	PhysicsComponent* physicsComponent = new PhysicsComponent("PhysicsComponent", cube, BodyType::DYNAMIC, 50);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createCube(string name, Vector3D position, Vector3D rotation, Vector3D scale)
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Cube* cube = new Cube(name, shader_byte_code, size_shader);
	//cube->setRigidBodyEnabled(true);
	cube->setPosition(position);
	cube->setRotation(rotation);
	cube->setScale(scale);
	objList.push_back(cube);
	PhysicsComponent* physicsComponent = new PhysicsComponent("PhysicsComponent", cube, BodyType::DYNAMIC, 50);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createPlane()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
	plane->setPosition(0, -5, 0);
	//plane->setRigidBodyEnabled(true);
	objList.push_back(plane);
	PhysicsComponent* physicsComponent = new PhysicsComponent("PhysicsComponent", plane, BodyType::STATIC, 10);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createSphere()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Sphere* sphere = new Sphere("Sphere", shader_byte_code, size_shader);
	//plane->setRigidBodyEnabled(true);
	objList.push_back(sphere);
	//PhysicsComponent* physicsComponent = new PhysicsComponent("PhysicsComponent", plane, BodyType::STATIC, 10);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return this->objList;
}

void GameObjectManager::createObjectFromFile(string name, string type, Vector3D position, Vector3D rotation, Vector3D scale)
{
	if (type == "Cube") {
		createCube(name, position, rotation, scale);
	}
}

void GameObjectManager::selectObject(AGameObject* obj)
{
	if (this->selectedObject != nullptr)
	{
		//	RESET PREV SELECTED OBJECT
		obj->isSelected = false;
	}

	obj->isSelected = true;
	this->selectedObject = obj;
}

void GameObjectManager::drawObjects(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	for (int i = 0; i < objList.size(); i++) {
		objList[i]->draw(width, height, vertex_shader, pixel_shader);
	}
}

GameObjectManager* GameObjectManager::get()
{
	static GameObjectManager gOManager;
	return &gOManager;
}

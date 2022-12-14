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
#include "Capsule.h"

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
	objList.push_back(cube);

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
	cube->setPosition(position);
	cube->setRotation(rotation);
	cube->setScale(scale);
	objList.push_back(cube);

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
	objList.push_back(plane);

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
	objList.push_back(sphere);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createCapsule()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Capsule* capsule = new Capsule("Capsule", shader_byte_code, size_shader);
	objList.push_back(capsule);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createMesh()
{
	//Create Mesh
	MeshPtr mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj", true);
	mesh->isTextured = false;
	mesh->setName("Static Mesh");
	objList.push_back(mesh.get());

	//Create Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
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

void GameObjectManager::EnablePhysics(bool isEnabled)
{
	for (int i = 0; i < objList.size(); i++) {
		objList[i]->rigidBodyEnabled = isEnabled;
	}
}


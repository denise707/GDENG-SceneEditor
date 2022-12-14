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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	GraphicsEngine::get()->getDevice()->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	GraphicsEngine::get()->getDevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	stbi_image_free(image_data);

	return true;
}

void GameObjectManager::initialize(void* shader_byte_code, size_t size_shader)
{
	width = UIManager::WINDOW_WIDTH;
	height = UIManager::WINDOW_HEIGHT;
	this->shader_byte_code = shader_byte_code;
	this->size_shader = size_shader;

	//Textured Shaders
	//Create Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"TexturedVertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	textured_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"TexturedPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	textured_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//DefaultShaders
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	default_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	default_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void GameObjectManager::createCube()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Cube* cube = new Cube("Cube " + to_string(index), shader_byte_code, size_shader);
	objList.push_back(cube);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	index++;
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
	Plane* plane = new Plane("Plane " + to_string(index), shader_byte_code, size_shader);
	objList.push_back(plane);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	index++;
}

void GameObjectManager::createSphere()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Sphere* sphere = new Sphere("Sphere " + to_string(index), shader_byte_code, size_shader);
	objList.push_back(sphere);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	index++;
}

void GameObjectManager::createCapsule()
{
	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Create Primitive
	Capsule* capsule = new Capsule("Capsule " + to_string(index), shader_byte_code, size_shader);
	objList.push_back(capsule);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	index++;
}

void GameObjectManager::createMesh(string name)
{
	//Create Mesh
	MeshPtr mesh;
	if (name == "armadillo") {
		mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj", false);
	}
	else if (name == "bunny") {
		mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj", false);
	}
	else if (name == "statue") {
		mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\statue.obj", false);
	}
	else if (name == "teapot") {
		mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj", true);
	}

	mesh->setName("Static Mesh " + to_string(index));
	objList.push_back(mesh.get());

	//Create Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	index++;
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
		updateTexture(objList[i]->isTextured, objList[i]->texture);
		if(objList[i]->isActive)
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

void GameObjectManager::updateTexture(bool isTextured, string textured)
{
	if (isTextured) {
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(textured_vs);
		GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(textured_ps);

		//Load Texture

		if (textured == "brick") {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\brick.png", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(texture);
		}
		else if (textured == "sand") {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\sand.jpg", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(texture);
		}
		else if (textured == "wood") {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\wood.jpg", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(texture);
		}
		else if (textured == "wall") {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\wall.jpg", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(texture);
		}
		else if (textured == "sky") {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\sky.jpg", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setTexture(texture);
		}
		else {
			ID3D11ShaderResourceView* texture;
			bool ret = LoadTextureFromFile("..\\Assets\\Textures\\sky.jpg", &texture);
			GraphicsEngine::get()->getImmediateDeviceContext()->setDefaultTexture(&texture);
		}
	}

	else {
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(default_vs);
		GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(default_ps);
	}
}
void GameObjectManager::saveEditStates()
{
	for (int i = 0; i < this->objList.size(); i++) 
	{
		this->objList[i]->saveEditState();
		cout << "saved: " << +" " + objList[i]->getName() + "\n";

	}
}

void GameObjectManager::restoreEditStates()
{

	for (int i = 0; i < this->objList.size(); i++) 
	{
		this->objList[i]->restoreEditState();
		cout << "restored: " << +" " + objList[i]->getName() + "\n";

	}
}

void GameObjectManager::updateAllObjectState(EditorAction* action)
{
	AGameObject* object = this->getObjectWithName(action->getName());
	if (object != nullptr) 
	{
		object->setPosition(action->getStorePos());
		object->setRotation(action->getStoredRotation());
		object->setScale(action->getStoredScale());
		object->getLocalMatrix() = action->getStoredMatrix();
	}
}

AGameObject* GameObjectManager::getObjectWithName(string name)
{
	for (int i = 0; i < this->objList.size(); i++)
	{
		if (objList[i]->getName() == name)
		{
			return objList[i];
		}
	}
	
	return  nullptr;
}



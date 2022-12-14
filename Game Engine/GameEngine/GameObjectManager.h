#pragma once
#include <vector>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "InputListener.h"

// buffers
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

// shaders
#include "VertexShader.h"
#include "PixelShader.h"

//math
#include "Matrix4x4.h"

//primitives
#include "Cube.h"
#include "Plane.h"

#include "Mesh.h"
#include "Vector3D.h"

class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
private:
	int width = 0;
	int height = 0;
	void* shader_byte_code;
	size_t size_shader;
	vector<AGameObject*> objList;
	VertexShader* m_vs;
	PixelShader* m_ps;
public:
	static GameObjectManager* get();
public:
	void drawObjects(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader);
	void initialize(void* shader_byte_code, size_t size_shader);
	void createCube();
	void createCube(string name, Vector3D position, Vector3D rotation, Vector3D scale);
	void createPlane();
	void createSphere();
	void createCapsule();
	void createMesh();

	vector<AGameObject*> getAllObjects();
	void createObjectFromFile(string name, string type, Vector3D position, Vector3D rotation, Vector3D scale);
	void EnablePhysics(bool isEnabled);

	void selectObject(AGameObject* obj);
	
	AGameObject* selectedObject = nullptr;
};



#pragma once
#include "AGameObject.h"
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
public:
	static GameObjectManager* get();
public:
	void drawObjects(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader);
	void initialize(void* shader_byte_code, size_t size_shader);
	void createCube();
	void createCube(string name, Vector3D position, Vector3D rotation, Vector3D scale);
	void createPlane();
	void createSphere();
	vector<AGameObject*> getAllObjects();
	void createObjectFromFile(string name, string type, Vector3D position, Vector3D rotation, Vector3D scale);
};


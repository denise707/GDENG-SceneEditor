#pragma once
#include "AGameObject.h"

class Sphere : public AGameObject
{
public:
	Sphere(string name, void* shaderByteCode, size_t sizeShader);
	~Sphere();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);
	void setRigidBodyEnabled(bool isEnabled);

private:
	float speed = 4.0f;
	float deltaTime = 0;
	Matrix4x4 m_world_matrix;

	UINT vertex_count;
	UINT start_vertex;
};


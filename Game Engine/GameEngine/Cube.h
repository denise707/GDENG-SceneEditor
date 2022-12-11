#pragma once
#include "AGameObject.h"

class Cube : public AGameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);
	void setRigidBodyEnabled(bool isEnabled);

private:
	float speed = 4.0f;
	float deltaTime = 0;
	Matrix4x4 m_world_matrix;
};


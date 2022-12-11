#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

class OutlineGizmo : public AGameObject
{
public:
	OutlineGizmo(string name, void* shaderByteCode, size_t sizeShader);
	~OutlineGizmo();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	float speed = 4.0f;
	float deltaTime = 0;
	Matrix4x4 m_world_matrix;
};


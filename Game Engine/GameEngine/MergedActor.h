#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <vector>
#include <unordered_map>

class MergedActor :
    public AGameObject
{
public:
	MergedActor(string name, void* shaderByteCode, size_t sizeShader, AGameObject* obj1, AGameObject* obj2);
	MergedActor(string name, void* shaderByteCode, size_t sizeShader, vector<AGameObject*> toCombine);

	~MergedActor();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);
	vector<Vertex> getVertexList();
private:
	ConstantBuffer* constantBuffer;

	float speed = 4.0f;
	float deltaTime = 0;
	Matrix4x4 m_world_matrix;
	vector<AGameObject*> objList;
	unordered_map<AGameObject*, VertexBuffer*> vertexBuffer_table;
	unordered_map<AGameObject*, IndexBuffer*> indexBuffer_table;
	unordered_map<AGameObject*, ConstantBuffer*> constantBuffer_table;
};


#pragma once
#include "Resource.h"
#include "TexturedVertexBuffer.h"
#include "IndexBuffer.h"
#include "AGameObject.h"

class Mesh : public Resource, public AGameObject
{
public:
	Mesh(const wchar_t* full_path, bool isTextured);
	~Mesh();
	TexturedVertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	bool isTextured = true;
private:
	TexturedVertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
private:
	friend class DeviceContext;
};
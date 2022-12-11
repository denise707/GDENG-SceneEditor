#pragma once
#include <d3d11.h>
#include "Texture.h"
#include "TexturedVertexBuffer.h"
#include "Prerequisites.h"

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	void setTexturedVertexBuffer(TexturedVertexBuffer* vertex_buffer);

	void drawPointList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

	void setDepthStencilState();

	void setTexture(const VertexShader* vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShader* pixel_shader, const TexturePtr& texture);
	void setDefaultTexture(ID3D11ShaderResourceView** out_srv);

	ID3D11DeviceContext* getDeviceContext();

	bool release();
	~DeviceContext();
protected:
	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;
};
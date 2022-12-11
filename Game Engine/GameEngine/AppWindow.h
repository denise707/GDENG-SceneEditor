#pragma once

#include <vector>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "InputListener.h"
#include "Mesh.h"

// buffers
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

// shaders
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void update();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	// Inherited via InputListener
	virtual void onMouseMove(const Point deltaPos) override;
	virtual void onLeftMouseDown(const Point deltaPos) override;
	virtual void onLeftMouseUp(const Point deltaPos) override;
	virtual void onRightMouseDown(const Point deltaPos) override;
	virtual void onRightMouseUp(const Point deltaPos) override;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;
	
private:
	int width = 0;
	int height = 0;;
	void* shader_byte_code;
	size_t size_shader;
	vector<MeshPtr> mesh_list;
};

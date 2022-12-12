#include "AppWindow.h"
#include <Windows.h>
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "imgui.h"
#include <d3d11.h>
#include "UIManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "EngineBackend.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GameObjectManager.h"

AppWindow::AppWindow()
{
	
}

void AppWindow::update()
{

}

AppWindow::~AppWindow()
{

}

void AppWindow::onCreate()
{
	Window::onCreate();
	
	//Initialize Input System
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	//Initialize Engine Time
	EngineTime::initialize();

	//Initialize Graphics Engine and Swap Chain
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//Release Compiled Shader
	GraphicsEngine::get()->releaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//Initialize Game Object Manager
	GameObjectManager::get()->initialize(shader_byte_code, size_shader);
	
	//Initialize Scene Camera
	SceneCameraHandler::initialize();

	//Initialize Base Component System
	BaseComponentSystem::initialize();

	//Initialize UIManager
	UIManager::getInstance()->initialize(Window::getHWND());

	//Initialize Engine Backend
	EngineBackend::getInstance()->initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//UPDATE BASED IN ENGINE STATE
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EDITOR)
	{
		//UPDATE PHYSICS
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	}
	else if (EngineBackend::getInstance()->getMode() == EngineBackend::PLAY)
	{
		//UPDATE PHYSICS
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	}
	else if (EngineBackend::getInstance()->getMode() == EngineBackend::PAUSED)
	{
		if (EngineBackend::getInstance()->insideFrameStep())
		{
			//UPDATE PHYSICS
			BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

			EngineBackend::getInstance()->endFrameStep();
		}
	}
	
	//DRAW OBJECTS
	GameObjectManager::get()->drawObjects(width, height, m_vs, m_ps);

	//UPDATE SCENE CAMERA
	SceneCameraHandler::getInstance()->update(EngineTime::getDeltaTime(), width, height);

	//DRAW UI SCREENS
	UIManager::getInstance()->drawAllUI();

	//PRESENT SWAP CHAIN
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{

}

void AppWindow::onKeyUp(int key)
{

}

void AppWindow::onMouseMove(const Point deltaPos)
{

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	
}


void AppWindow::onRightMouseDown(const Point deltaPos)
{
	
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{

}

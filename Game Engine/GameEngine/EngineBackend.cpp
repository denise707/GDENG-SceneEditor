#include "EngineBackend.h"
#include "GameObjectManager.h"

EngineBackend* EngineBackend::sharedInstance = NULL;

EngineBackend* EngineBackend::getInstance()
{
	return sharedInstance;
}

void EngineBackend::initialize()
{
	sharedInstance = new EngineBackend();
}

void EngineBackend::destroy()
{
	delete sharedInstance;
}

void EngineBackend::setMode(EditorMode mode)
{
	this->editorMode = mode;

	if (this->editorMode == EditorMode::PLAY) 
	{
		// save when set to play
		GameObjectManager::get()->saveEditStates();
		cout << "Set to Play mode\n";

	}
	else if (this->editorMode == EditorMode::EDITOR) 
	{	
		//restore when in editor mode
		GameObjectManager::get()->restoreEditStates();
		cout << "Set to Editor mode\n";

	}
	else if (this->editorMode == EditorMode::PAUSED)
	{
		cout << "Set to Paused mode\n";
	}
}

void EngineBackend::startFrameStep()
{
	this->frameStepping = true;
}

void EngineBackend::endFrameStep()
{
	this->frameStepping = false;
}

bool EngineBackend::insideFrameStep()
{
	return this->frameStepping;
}

EngineBackend::EditorMode EngineBackend::getMode()
{
	return this->editorMode;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{

}
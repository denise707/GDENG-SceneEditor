#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = NULL;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (sharedInstance != NULL) {
		delete sharedInstance;
	}
}

InputSystem::InputSystem()
{
	this->oldMousePos = Point(0, 0);
}

InputSystem::~InputSystem()
{
	this->inputListenerList.clear();
}

void InputSystem::addListener(InputListener* listener)
{
	this->inputListenerList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	//find object in used
	int index = -1;
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		if (this->inputListenerList[i] == listener) {
			index = i;
			break;
		}
	}
	if (index > -1) {
		this->inputListenerList.erase(this->inputListenerList.begin() + index);
	}
}

void InputSystem::update()
{

	POINT currentPt = {};
	GetCursorPos(&currentPt);

	if (this->firstTimeCall) {
		this->firstTimeCall = false;
		this->oldMousePos = Point(currentPt.x, currentPt.y);
	}

	if (this->oldMousePos.m_x != currentPt.x || this->oldMousePos.m_y != currentPt.y)
	{
		Point deltaPt = Point(currentPt.x - this->oldMousePos.m_x, currentPt.y - this->oldMousePos.m_y);
		this->onMouseMove(deltaPt);
	}

	this->oldMousePos = Point(currentPt.x, currentPt.y);

	if (GetKeyboardState(this->keyStates)) {
		for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
			if (this->keyStates[i] & 0x80 && this->keyStates[i] != this->oldKeyStates[i]) {
				if (i == VK_LBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.m_x, currentPt.y - this->oldMousePos.m_y);
					this->onLeftMouseDown(deltaPt);
				}
				else if (i == VK_RBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.m_x, currentPt.y - this->oldMousePos.m_y);
					this->onRightMouseDown(deltaPt);
				}
				else {
					this->callOnKeyDown(i);
				}
			}
			else if (this->keyStates[i] != this->oldKeyStates[i]) {
				if (i == VK_LBUTTON && this->keyStates[i] != this->oldKeyStates[i]) {
					Point deltaPt = Point(currentPt.x - this->oldMousePos.m_x, currentPt.y - this->oldMousePos.m_y);
					this->onLeftMouseUp(deltaPt);
				}
				else if (i == VK_RBUTTON && this->keyStates[i] != this->oldKeyStates[i]) {
					Point deltaPt = Point(currentPt.x - this->oldMousePos.m_x, currentPt.y - this->oldMousePos.m_y);
					this->onRightMouseUp(deltaPt);
				}
				else {
					this->callOnKeyUp(i);
				}
			}
		}

		//store current keys to old states
		::memcpy(this->oldKeyStates, this->keyStates, sizeof(unsigned char) * 256);
	}
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
		if (this->keyStates[i] & 0x80 && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}


	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
		if (!(this->keyStates[i] & 0x80) && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}

	return false;
}

void InputSystem::callOnKeyDown(int key)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onKeyUp(key);
	}
}

void InputSystem::onMouseMove(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onMouseMove(deltaPt);
	}
}

void InputSystem::onLeftMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseDown(deltaPt);
	}
}

void InputSystem::onLeftMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseUp(deltaPt);
	}
}

void InputSystem::onRightMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseDown(deltaPt);
	}
}

void InputSystem::onRightMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseUp(deltaPt);
	}
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

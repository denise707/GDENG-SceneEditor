#pragma once
#include <iostream>
#include "InputListener.h"
#include <Windows.h>
#include <vector>
#include "Point.h"

typedef std::vector<InputListener*> Lists;

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	void update();

	bool isKeyDown(int key);
	bool isKeyUp(int key);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};             // copy constructor is private
	InputSystem& operator=(InputSystem const&) {};  // assignment operator is private*/

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void onMouseMove(Point deltaPt);
	void onLeftMouseDown(Point deltaPt);
	void onLeftMouseUp(Point deltaPt);
	void onRightMouseDown(Point deltaPt);
	void onRightMouseUp(Point deltaPt);

	static InputSystem* sharedInstance;
	Lists inputListenerList;
	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};

	Point oldMousePos;
	bool firstTimeCall = true;
};
#pragma once
#define NOMINMAX //To avoid conflict with Windows.h MIN and MAX declarations
#include <Windows.h>

class Window
{
public:
	Window();

	//Initialize the window
	bool init();
	bool broadcast();

	//Release the window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//Events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	HWND getHWND();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AppWindow.h"
#include "AUIScreen.h"

class UINames
{
public:
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String COLOR_PICKER_SCREEN = "COLOR_PICKER_SCREEN";
	const String PLACE_HOLDER_SCREEN = "PLACE_HOLDER_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
};

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1024;
	static const int WINDOW_HEIGHT = 768;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};


#pragma once
#include "AUIScreen.h"
#include <vector>
class UIManager;

class DebugScreen : public AUIScreen
{
private:
	DebugScreen();
	~DebugScreen();

	virtual void drawUI() override;


	friend class UIManager;

	std::vector<String> logsList;

public:
	void printText(String text);
	static bool isOpen;


};


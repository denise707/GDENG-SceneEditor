#pragma once
#include "AUIScreen.h"

class UIManager;
class SceneControlsScreen : public AUIScreen
{
private:
	SceneControlsScreen();
	~SceneControlsScreen();

	virtual void drawUI() override;
	friend class UIManager;

public:
	static bool isOpen;
};





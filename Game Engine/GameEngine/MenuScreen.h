#pragma once
#include "AUIScreen.h"
#include "PixelShader.h"

class UIManager;
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;
	friend class UIManager;

private:
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;

	void saveScene();
	void loadScene();
	int index = 0;
};


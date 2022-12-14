#pragma once
#include "AUIScreen.h"
class InspectorScreen : public AUIScreen
{
	InspectorScreen();
	~InspectorScreen();

	virtual void drawUI() override;
	friend class UIManager;

public:
	static bool isOpen;
	std::string modelFilename;
	void enterFilename();
	void enterTexName();
	static bool openFilenameGetter;
	bool openTexnameGetter = false;
private:
	float posDisp[3] = { 0.0f, 0.0f, 0.0f };
	float rotDisp[3] = { 0.0f, 0.0f, 0.0f };
	float scaleDisp[3] = { 1.0f, 1.0f, 1.0f };

	void updateTransform();
	void updatePhysicsComponent(bool attach);
	void updateTextureComponent(bool attach);
};


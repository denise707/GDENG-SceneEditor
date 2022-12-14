#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	//capture object state
	this->objectName = gameObject->getName();
	this->localPosition = gameObject->getLocalPosition();
	this->localScale = gameObject->getLocalScale();
	this->localRotation= gameObject->getLocalRotation();
	this->localMatrix = gameObject->getLocalMatrix();
}

EditorAction::~EditorAction()
{

}

std::string EditorAction::getName()
{
	return this->objectName;
}

Vector3D EditorAction::getStorePos()
{
	return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
	return this->localScale;
}

Vector3D EditorAction::getStoredRotation()
{
	return this->localRotation;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return this->localMatrix;
}
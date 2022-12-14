#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObject.h"

//an action performed by the user in the editor. Stores a snapshot for undoing and redoing
class EditorAction
{
public:
	EditorAction(AGameObject* gameObject);
	~EditorAction();

	std::string getName();
	Vector3D getStorePos();
	Vector3D getStoredScale();
	Vector3D getStoredRotation();
	Matrix4x4 getStoredMatrix();

private:
	std::string objectName;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

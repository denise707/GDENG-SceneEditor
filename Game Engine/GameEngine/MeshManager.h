#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	MeshPtr createMeshFromFile(const wchar_t* file_path, bool tx);
	bool isTextured = false;
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};


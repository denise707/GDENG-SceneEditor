#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path, bool isTextured)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path, isTextured));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path, this->isTextured);
	}
	catch (...) {}

	return mesh;
}

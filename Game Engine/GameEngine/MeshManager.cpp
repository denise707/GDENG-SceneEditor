#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}


MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path, bool tx)
{
	isTextured = tx;
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path, tx));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path, isTextured);
	}
	catch (...) {}

	return mesh;
}

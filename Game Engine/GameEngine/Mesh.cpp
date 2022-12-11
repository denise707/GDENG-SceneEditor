#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexMesh.h"
#include <iostream>
#include "SceneCameraHandler.h"

Mesh::Mesh(const wchar_t* full_path, bool isTextured) : Resource(full_path), AGameObject(name)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");


	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;

				if (isTextured) {
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	m_vertex_buffer = GraphicsEngine::get()->createMeshVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_vertex_buffer->load(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);

	m_index_buffer = GraphicsEngine::get()->createIndexBuffer();
	m_index_buffer->load(&list_indices[0], (UINT)list_indices.size());

	//Create constant buffer
	CBData cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

Mesh::~Mesh()
{

}

TexturedVertexBuffer* Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return m_index_buffer;
}

void Mesh::update(float deltaTime)
{

}

void Mesh::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	CBData cbData = {};

	//Add object transformation
	Matrix4x4 temp;

	cbData.worldMatrix.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setScale(getLocalScale());
	cbData.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(getLocalRotation().m_x);
	cbData.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(getLocalRotation().m_y);
	cbData.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationZ(getLocalRotation().m_z);
	cbData.worldMatrix *= temp;

	temp.setIdentity();
	temp.setTranslation(getLocalPosition());
	cbData.worldMatrix *= temp;

	//Add camera transformation
	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.viewMatrix = cameraMatrix;

	//Perspective View
	cbData.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(vertexShader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, this->constantBuffer);

	deviceContext->setIndexBuffer(getIndexBuffer());
	deviceContext->setTexturedVertexBuffer(getVertexBuffer());

	deviceContext->drawIndexedTriangleList(this->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

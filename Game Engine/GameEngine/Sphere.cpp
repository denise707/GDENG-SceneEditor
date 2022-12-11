#include "Sphere.h"
#include <iostream>
#include "DeviceContext.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"

#define PI 3.14159265359

float map(int value, int minA, int maxA, float minB, float maxB) {
	return (maxB - minB) * (value - minA) / (maxA - minA) + minB;
}

Sphere::Sphere(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//Create buffers for drawing. Vertex data that needs to be drawn are temporarily placed here.
	//Vertex vertex_list[] =
	//{
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0,1,0) },
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(0,1,0), Vector3D(0,1,1) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,0), Vector3D(0,0,1) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,0,0), Vector3D(0,1,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1,1) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,1,0), Vector3D(0,0,1) }
	//};

	float r = 100;
	int total = 100;
	Vertex vertex_list[100];

	for (int i = 0; i < total; i++) {
		float lon = map(i, 0, total, -PI, PI);
		
		for (int j = 0; j < total; j++) {
			float lat = map(j, 0, total, -PI/2, PI/2);
			float x = r * sinf(lon) * cosf(lat);
			float y = r * sinf(lon) * sinf(lat);
			float z = r * cosf(lon);

			cout << z/100 << endl;

			Vertex vertex = {Vector3D(x/100, y/100, z/100), Vector3D(1, 0, 0), Vector3D(1, 1, 1)};
			vertex_list[i] = vertex;
		}
	}

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(vertex_list, sizeof(Vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0, 1, 2,
		2, 3, 0,
		//BACK SIDE
		4, 5, 6,
		6, 7, 4,
		//TOP SIDE
		1, 6, 5,
		5, 2, 1,
		//BOTTOM SIDE
		7, 0, 3,
		3, 4, 7,
		//RIGHT SIDE
		3, 2, 5,
		5, 4, 3,
		//LEFT SIDE
		7, 6, 1,
		1, 0, 7
	};

	vertex_count = ARRAYSIZE(vertex_list);
	start_vertex = 0;

	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(index_list, ARRAYSIZE(index_list));

	//Create constant buffer
	CBData cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));

	//Set animation speed
	setAnimSpeed(4);
	this->type = "Sphere";
}

Sphere::~Sphere()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
}

void Sphere::update(float delta_time)
{
	//For animation
	/*float newRotX = getLocalRotation().m_x + (delta_time * speed);
	float newRotY = getLocalRotation().m_y + (delta_time * speed);
	float newRotZ = getLocalRotation().m_z + (delta_time * speed);

	setRotation(newRotX, newRotY, newRotZ);

	deltaTime += delta_time;*/

}

void Sphere::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	CBData cbData = {};

	cbData.time = deltaTime;

	//Add object transformation
	Matrix4x4 temp;

	//Save this
	cbData.worldMatrix.setIdentity();
	//Save this

	//For objects with physics
	if (rigidBodyEnabled) {
		cbData.worldMatrix = this->localMatrix;
	}

	//For objects without physics
	else {
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
	}

	//Add camera transformation
	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.viewMatrix = cameraMatrix;

	//Perspective View
	cbData.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(vertex_shader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixel_shader, this->constantBuffer);

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawTriangleStrip(vertex_count, start_vertex);
	//deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Sphere::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Sphere::setRigidBodyEnabled(bool isEnabled)
{
	this->rigidBodyEnabled = isEnabled;
}



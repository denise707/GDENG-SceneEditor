#include "AGameObject.h"
#include <iostream>

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D(0, 0, 0);
	this->localRotation = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
}

AGameObject::~AGameObject()
{

}

void AGameObject::update(float deltaTime)
{
}

void AGameObject::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

VertexBuffer* AGameObject::getVertexBuffer()
{
	return vertexBuffer;
}

IndexBuffer* AGameObject::getIndexBuffer()
{
	return indexBuffer;
}

ConstantBuffer* AGameObject::getConstantBuffer()
{
	return constantBuffer;
}

string AGameObject::getName()
{
	return this->name;
}

void AGameObject::setName(string name)
{
	this->name = name;
}

void AGameObject::setLocalMatrix(float matrix[16])
{
	Matrix4x4 mat;
	mat.m_mat[0][0] = matrix[0];
	mat.m_mat[0][1] = matrix[1];
	mat.m_mat[0][2] = matrix[2];
	mat.m_mat[0][3] = matrix[3];

	mat.m_mat[1][0] = matrix[4];
	mat.m_mat[1][1] = matrix[5];
	mat.m_mat[1][2] = matrix[6];
	mat.m_mat[1][3] = matrix[7];

	mat.m_mat[2][0] = matrix[8];
	mat.m_mat[2][1] = matrix[9];
	mat.m_mat[2][2] = matrix[10];
	mat.m_mat[2][3] = matrix[11];

	mat.m_mat[3][0] = matrix[12];
	mat.m_mat[3][1] = matrix[13];
	mat.m_mat[3][2] = matrix[14];
	mat.m_mat[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(mat);
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->localScale); 
	Matrix4x4 transMatrix; transMatrix.setIdentity(); transMatrix.setTranslation(this->localPosition);
	localMatrix.setIdentity();
	this->localMatrix *= scaleMatrix; 
	this->localMatrix *= transMatrix; 
	this->localMatrix *= newMatrix; 

	this->simulatePhysics = true;
}

void AGameObject::awake()
{

}




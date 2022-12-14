#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner, BodyType bodyType, float nmass) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	//Whenever a new physics componennt is initialized. Register to physics system
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	//Create a rigid body in the world
	Vector3D scale = getOwner()->getLocalScale();
	Transform transform;
	transform.setPosition(Vector3(getOwner()->getLocalPosition().m_x, getOwner()->getLocalPosition().m_y, getOwner()->getLocalPosition().m_z));
	transform.setOrientation(Quaternion::fromEulerAngles(Vector3(getOwner()->getLocalRotation().m_x, getOwner()->getLocalRotation().m_y, getOwner()->getLocalRotation().m_z)));

	if (owner->type == "Cube")
	{
		BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2)); //half extent
		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(boxShape, transform);
	}

	else if (owner->type == "Plane")
	{
		BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x * 2.0f, scale.m_y / 20, scale.m_z * 2.0f)); //half extent
		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(boxShape, transform);
	}

	else if (owner->type == "Sphere")
	{
		SphereShape* sphereShape = physicsCommon->createSphereShape(((getOwner()->getLocalScale().m_x + getOwner()->getLocalScale().m_y + getOwner()->getLocalScale().m_z)/ 3.0f) /2.0f); //half extent
		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(sphereShape, transform);
	}

	else if (owner->type == "Capsule")
	{
		float radius = ((getOwner()->getLocalScale().m_x +getOwner()->getLocalScale().m_z) / 2.0f) / 2.0f;
		float height = getOwner()->getLocalScale().m_y;
		CapsuleShape* capsuleShape = physicsCommon->createCapsuleShape(radius, height); //half extent
		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(capsuleShape, transform);
	}
	
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(nmass);
	this->rigidBody->setType(bodyType);
		
	transform = rigidBody->getTransform();
	float matrix[16];
	//transform.getOpenGLMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];

	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}

void PhysicsComponent::setMass(float mass)
{
	this->mass = mass;
}
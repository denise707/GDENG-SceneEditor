#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner, BodyType bodyType, float mass);
	~PhysicsComponent();
	void perform(float deltaTime) override;
	RigidBody* getRigidBody();
	void setMass(float mass);
private:
	float mass = 50.0f; //in kilograms
	RigidBody* rigidBody;
};
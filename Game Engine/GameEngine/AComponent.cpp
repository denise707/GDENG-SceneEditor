#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(AGameObject* owner)
{
	this->owner = owner;
}

void AComponent::detachOwner()
{
	this->owner = NULL;
}

AGameObject* AComponent::getOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
	return this->type;
}

AComponent::String AComponent::getName()
{
	return this->name;
}

void AComponent::perform(float deltaTime)
{
}

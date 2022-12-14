#include "InspectorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <iostream>
#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

bool InspectorScreen::isOpen = false;

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{

}

InspectorScreen::~InspectorScreen()
{
    AUIScreen::~AUIScreen();
}

void InspectorScreen::drawUI()
{
    string currGO = {};
    bool currGOPhys;

    if (isOpen)
    {

        ImGui::SetNextWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
        ImGui::Begin("Inspector", &isOpen);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (GameObjectManager::get()->selectedObject)
        {
            currGO = GameObjectManager::get()->selectedObject->getName();
            currGOPhys = GameObjectManager::get()->selectedObject->physicsEnabled;
            ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(currGO.c_str());
            ImGui::Spacing();
            ImGui::Text("Object Properties: ");

            if (ImGui::Checkbox("Active", &(GameObjectManager::get()->selectedObject->isActive))) {

            }
            if (ImGui::InputFloat3("Position", this->posDisp, "% .3f"))
            { 
                this->updateTransform(); 
            }
            if (ImGui::InputFloat3("Rotation", this->rotDisp, "% .3f"))
            { 
                this->updateTransform(); 
            }
            if (ImGui::InputFloat3("Scale", this->scaleDisp, "% .3f"))
            { 
                this->updateTransform();
            }
            if (ImGui::Checkbox("Attach Physics Component", &currGOPhys)) {
                this->updatePhysicsComponent(currGOPhys);
            }
            if (ImGui::Checkbox("Attach Texture Component", &isOpen)) {

            }
            if (ImGui::Button("Delete Game Object")) {

            }
        }
        ImGui::End();
    }
}

void InspectorScreen::updateTransform()
{

    GameObjectManager::get()->selectedObject->setPosition(this->posDisp[0], this->posDisp[1], this->posDisp[2]);
    GameObjectManager::get()->selectedObject->setRotation(this->rotDisp[0], this->rotDisp[1], this->rotDisp[2]);
    GameObjectManager::get()->selectedObject->setScale(this->scaleDisp[0], this->scaleDisp[1], this->scaleDisp[2]);
}

void InspectorScreen::updatePhysicsComponent(bool attach) {
    if (attach) {
        PhysicsComponent* physicsComponent = new PhysicsComponent("PhysicsComponent", GameObjectManager::get()->selectedObject, BodyType::DYNAMIC, 50);
        GameObjectManager::get()->selectedObject->physicsComponent = physicsComponent;
        GameObjectManager::get()->selectedObject->physicsEnabled = true;
    }
    else {
        BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(GameObjectManager::get()->selectedObject->physicsComponent);
        GameObjectManager::get()->selectedObject->physicsComponent = NULL;
        GameObjectManager::get()->selectedObject->physicsEnabled = false;
    }
}

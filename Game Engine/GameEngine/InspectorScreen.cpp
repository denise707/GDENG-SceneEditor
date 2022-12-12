#include "InspectorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <iostream>

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
            ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(currGO.c_str());
            ImGui::Spacing();
            ImGui::Text("Object Properties: ");

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

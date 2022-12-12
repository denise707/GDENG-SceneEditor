#include "InspectorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
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

            AGameObject* obj = GameObjectManager::get()->selectedObject;
            Vector3D v;
            v = obj->getLocalPosition();
            posDisp[0] = v.m_x; posDisp[1] = v.m_y; posDisp[2] = v.m_z;

            v = obj->getLocalRotation();
            rotDisp[0] = v.m_x; rotDisp[1] = v.m_y; rotDisp[2] = v.m_z;

            v = obj->getLocalScale();
            scaleDisp[0] = v.m_x; scaleDisp[1] = v.m_y; scaleDisp[2] = v.m_z;

            if (ImGui::InputFloat3("Position", this->posDisp, "% .2f"))
            { 
                this->updateTransform(); 
            }
            if (ImGui::InputFloat3("Rotation", this->rotDisp, "% .2f"))
            { 
                this->updateTransform(); 
            }
            if (ImGui::InputFloat3("Scale", this->scaleDisp, "% .2f"))
            { 
                this->updateTransform();
            }

        }
     


        ImGui::End();
    }
}

void InspectorScreen::updateTransform()
{

 
    AGameObject* obj = GameObjectManager::get()->selectedObject;
    obj->setPosition(this->posDisp[0], this->posDisp[1], this->posDisp[2]);
    obj->setRotation(this->rotDisp[0], this->rotDisp[1], this->rotDisp[2]);
    obj->setScale(this->scaleDisp[0], this->scaleDisp[1], this->scaleDisp[2]);

    //if (obj->physicsComp)
    //{
    //    //((PhysicsComponent*)obj->physicsComp)->updateRigidBody();
    //}


}

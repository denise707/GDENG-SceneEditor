#include "InspectorScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <iostream>
#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include"ActionHistory.h"

bool InspectorScreen::isOpen = true;
bool InspectorScreen::openFilenameGetter = false;

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
    bool currGOTex;

    if (isOpen)
    {

        ImGui::SetNextWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
        ImGui::Begin("Inspector", &isOpen);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (AGameObject* selectedObj = GameObjectManager::get()->selectedObject)
        {   
            currGO = GameObjectManager::get()->selectedObject->getName();
            currGOPhys = GameObjectManager::get()->selectedObject->physicsEnabled;
            currGOTex = GameObjectManager::get()->selectedObject->isTextured;
            ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(currGO.c_str());
            ImGui::Spacing();
            ImGui::Text("Object Properties: ");

            Vector3D v;
            v = selectedObj->getLocalPosition();
            posDisp[0] = v.m_x; posDisp[1] = v.m_y; posDisp[2] = v.m_z;

            v = selectedObj->getLocalScale();
            scaleDisp[0] = v.m_x; scaleDisp[1] = v.m_y; scaleDisp[2] = v.m_z;

            v = selectedObj->getLocalRotation();
            rotDisp[0] = v.m_x; rotDisp[1] = v.m_y; rotDisp[2] = v.m_z;




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
            if (ImGui::Checkbox("Attach Texture Component", &currGOTex)) {
                this->updateTextureComponent(currGOTex);
                GameObjectManager::get()->selectedObject->texture = " ";
            }
            if (ImGui::Button("Change Texture")) {
                openTexnameGetter = true;
            }
            if (ImGui::Button("Delete Game Object")) {
                GameObjectManager::get()->deleteObject();
            }

        }
        ImGui::End();
    }

    enterFilename();
    enterTexName();
}

void InspectorScreen::enterFilename() {
    if (openFilenameGetter) {
        ImGui::SetNextWindowSize(ImVec2(250, 200));
        ImGui::Begin("Models");
        ImGui::Spacing();
        if (ImGui::Button("Armadillo")) {
            modelFilename = "armadillo"; GameObjectManager::get()->createMesh(modelFilename);
        }
        if (ImGui::Button("Bunny")) {
            modelFilename = "bunny"; GameObjectManager::get()->createMesh(modelFilename);
        }
        if (ImGui::Button("Lucy")) {
            modelFilename = "statue"; GameObjectManager::get()->createMesh(modelFilename);
        }
        if (ImGui::Button("Teapot")) {
            modelFilename = "teapot"; GameObjectManager::get()->createMesh(modelFilename);
        }
        ImGui::End();
    }
}

void InspectorScreen::enterTexName()
{
    if (openTexnameGetter) {
        ImGui::SetNextWindowSize(ImVec2(250, 200));
        ImGui::Begin("Textures");
        ImGui::Spacing();
        if (ImGui::Button("Brick")) {
            GameObjectManager::get()->selectedObject->texture = "brick";
        }
        if (ImGui::Button("Sand")) {
            GameObjectManager::get()->selectedObject->texture = "sand";
        }
        if (ImGui::Button("Wood")) {
            GameObjectManager::get()->selectedObject->texture = "wood";
        }
        if (ImGui::Button("Wall")) {
            GameObjectManager::get()->selectedObject->texture = "wall";
        }
        if (ImGui::Button("Sky")) {
            GameObjectManager::get()->selectedObject->texture = "sky";
        }
        ImGui::End();
    }
}


void InspectorScreen::updateTransform()
{

    if (GameObjectManager::get()->selectedObject)
    {
        // record every after update
        ActionHistory::getInstance()->recordAction(GameObjectManager::get()->selectedObject);
        GameObjectManager::get()->selectedObject->setPosition(this->posDisp[0], this->posDisp[1], this->posDisp[2]);
        GameObjectManager::get()->selectedObject->setRotation(this->rotDisp[0], this->rotDisp[1], this->rotDisp[2]);
        GameObjectManager::get()->selectedObject->setScale(this->scaleDisp[0], this->scaleDisp[1], this->scaleDisp[2]);
    }

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

void InspectorScreen::updateTextureComponent(bool attach)
{
    GameObjectManager::get()->selectedObject->isTextured = attach;
}

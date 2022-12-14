#include "HierarchyScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <iostream>

bool HierarchyScreen::isOpen = true;

HierarchyScreen::HierarchyScreen() : AUIScreen("HierarchyScreen")
{

}

HierarchyScreen::~HierarchyScreen()
{
    AUIScreen::~AUIScreen();
}

void HierarchyScreen::drawUI()
{
    if (isOpen)
    {
     
        ImGui::SetNextWindowSize(ImVec2(200, UIManager::WINDOW_HEIGHT));
        ImGui::Begin("Hierarchy", &isOpen, ImGuiWindowFlags_NoResize);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        for (int i = 0; i < GameObjectManager::get()->getAllObjects().size(); i++)
        {
           // string currGO = {};
            /*currGO = GameObjectManager::get()->getAllObjects().at(i)->getName();
            ImGui::Text(currGO.c_str());*/

            string label;
            label = GameObjectManager::get()->getAllObjects().at(i)->getName()+ "##" +  to_string(i);
            const char* objLabel = label.data();

            if (ImGui::Button(objLabel, ImVec2(150, 20)))
            {
                AGameObject* selObj = GameObjectManager::get()->getAllObjects().at(i);
                GameObjectManager::get()->selectObject(selObj);

            }

        }


        ImGui::End();
    }
}

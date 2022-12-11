#include "HierarchyScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include <iostream>

bool HierarchyScreen::isOpen = false;

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
        ImGui::SetNextWindowSize(ImVec2(200, 200));
        ImGui::Begin("Hierarchy", &isOpen, ImGuiWindowFlags_NoResize);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::End();
    }
}

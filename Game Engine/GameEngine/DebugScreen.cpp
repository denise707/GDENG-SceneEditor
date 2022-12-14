#include "DebugScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include <iostream>

bool DebugScreen::isOpen = true;

DebugScreen::DebugScreen() : AUIScreen("DebugScreen")
{
    printText("created debug screen");
}

DebugScreen::~DebugScreen()
{
}

void DebugScreen::drawUI()
{
    if (isOpen)
    {

        ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH, 300));
        ImGui::Begin("Log Window", &isOpen, ImGuiWindowFlags_NoResize);
        ImGui::Spacing();

        for (int i = 0; i < logsList.size(); i++)
        {
            string label;
            label = logsList[i];
            const char* objLabel = label.data();
            ImGui::Text(objLabel);


        }



        ImGui::End();
    }
}

void DebugScreen::printText(String text)
{
    logsList.push_back(text);
}

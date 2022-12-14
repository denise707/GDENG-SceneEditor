#include "SceneControlsScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "EngineBackend.h"
#include <iostream>

bool SceneControlsScreen::isOpen = false;

SceneControlsScreen::SceneControlsScreen() : AUIScreen("SceneControlsScreen")
{

}

SceneControlsScreen::~SceneControlsScreen()
{
    AUIScreen::~AUIScreen();
}

void SceneControlsScreen::drawUI()
{
    if (isOpen)
    {

        //ImGui::SetNextWindowSize(ImVec2(200, 50));
        ImGui::Begin("Scene Ctrls", &isOpen, ImGuiWindowFlags_NoResize |ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        // content

        string label;
        label = "Play";
        const char* playerScene = label.data();
        if (ImGui::Button(playerScene, ImVec2(50, 20)))
        {
            EngineBackend::getInstance()->setMode(EngineBackend::PLAY);
            cout << "Play Scene\n";
        }

        ImGui::SameLine();

        label = "Pause";
        const char* pauseScene = label.data();

        if (ImGui::Button(pauseScene, ImVec2(50, 20)))
        {
            EngineBackend::getInstance()->setMode(EngineBackend::PAUSED);

        }


        ImGui::End();
    }
}

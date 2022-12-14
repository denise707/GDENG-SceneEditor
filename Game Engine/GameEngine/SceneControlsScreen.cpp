#include "SceneControlsScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "EngineBackend.h"
#include <iostream>

bool SceneControlsScreen::isOpen = true;

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
        ImGui::Begin("Engine Controls", &isOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        // content            
        string label;


         // ENGINE STATES
        ImGui::Text("Engine State Controls");
        if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR || EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::PAUSED)
        {
            label = "Play";
            const char* playerScene = label.data();
            if (ImGui::Button(playerScene, ImVec2(50, 20)))
            {
                EngineBackend::getInstance()->setMode(EngineBackend::PLAY);
                cout << "Play Scene\n";
            }

            if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::PAUSED)
            {
                ImGui::Spacing();
                // EDITOR STATES
                ImGui::Text("Edtior State Controls");
                label = "UNDO";
                const char* undoState = label.data();
                if (ImGui::Button(undoState, ImVec2(50, 20)))
                {

                    cout << "Undo Scene\n";
                }
                ImGui::SameLine;
                label = "REDO";
                const char* redoState = label.data();
                if (ImGui::Button(redoState, ImVec2(50, 20)))
                {
                    cout << "Redo Scene\n";
                }
            }
        }  
        
        if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::PLAY)
        {
            // DISPLAY PAUSE BUTTON AND STOP WHEN IN OTHER STATES
            label = "Pause";
            const char* pauseScene = label.data();
            if (ImGui::Button(pauseScene, ImVec2(50, 20)))
            {
                EngineBackend::getInstance()->setMode(EngineBackend::PAUSED);
                cout << "Pause Scene\n";
            }
        }

        if(EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::PAUSED || EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::PLAY)
        {
            ImGui::SameLine;

            label = "Stop";
            const char* stopScene = label.data();
            if (ImGui::Button(stopScene, ImVec2(50, 20)))
            {
                EngineBackend::getInstance()->setMode(EngineBackend::EDITOR);
                cout << "Stop Scene\n";
            }
        }


        
       


        ImGui::End();
    }
}

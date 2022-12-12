#include "MenuScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "HierarchyScreen.h"
#include "InspectorScreen.h"
#include "SceneControlsScreen.h"
#include "GameObjectManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::fstream FileWriter;
typedef std::fstream FileReader;

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{

}

MenuScreen::~MenuScreen()
{
    AUIScreen::~AUIScreen();
}

void MenuScreen::drawUI()
{
    bool* p_open = new bool;
    *p_open = true;
    ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT));
	if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Create Physics Cube..")) { GameObjectManager::get()->createCube(); }
            if (ImGui::MenuItem("Create Physics Plane..")) { GameObjectManager::get()->createPlane(); }
			if (ImGui::MenuItem("Create Sphere..")) { GameObjectManager::get()->createSphere(); }
            if (ImGui::MenuItem("Save Scene..")) { saveScene(); }
			if (ImGui::MenuItem("Load Scene..")) { loadScene(); }
            ImGui::EndMenu();
        }
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Heirarchy")) { HierarchyScreen::isOpen = true; }
			if (ImGui::MenuItem("Inspector")) { InspectorScreen::isOpen = true; }
			if (ImGui::MenuItem("Scene Controls")) { SceneControlsScreen::isOpen = true; }
			ImGui::EndMenu();
		}
        ImGui::EndMainMenuBar();
    }
}

void MenuScreen::saveScene()
{
		// CHECK 
	String fileDir = "D:\\Academics\\Study References\\DLSU 4th Year - Term 1\\GDENG2\\Final Exam\\Game Engine\\SavedFiles\\" + to_string(index) +  ".iet";

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

	vector<AGameObject*> allObjects = GameObjectManager::get()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++) {
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "Type: " << allObjects[i]->type << std::endl;
		sceneFile << "Rigid Body Enabled: " << allObjects[i]->rigidBodyEnabled << std::endl;
		sceneFile << "Position: " << position.m_x << " " << position.m_y << " " << position.m_z << std::endl;
		sceneFile << "Rotation: " << rotation.m_x << " " << rotation.m_y << " " << rotation.m_z << std::endl;
		sceneFile << "Scale: " << scale.m_x << " " << scale.m_y << " " << scale.m_z << std::endl;
	}
	sceneFile.close();
}

std::vector<std::string> split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void MenuScreen::loadScene()
{
	String fileDir = "D:\\Academics\\Study References\\DLSU 4th Year - Term 1\\GDENG2\\Final Exam\\Game Engine\\SavedFiles\\" + to_string(index) + ".iet";

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	String objectType;
	String objectRigidBody;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) {
			std::vector<std::string> stringSplit = split(readLine, ' ');
			objectType = stringSplit[1];
			index++;
		}
		else if (index == 2) {
			std::vector<std::string> stringSplit = split(readLine, ' ');
			objectRigidBody = stringSplit[1];
			index++;
		}
		else if (index == 3) {
			std::vector<std::string> stringSplit = split(readLine, ' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) {
			std::vector<std::string> stringSplit = split(readLine, ' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 5) {
			std::vector<std::string> stringSplit = split(readLine, ' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			GameObjectManager::get()->createObjectFromFile(objectName, objectType, position, rotation, scale);
		}
	}
}



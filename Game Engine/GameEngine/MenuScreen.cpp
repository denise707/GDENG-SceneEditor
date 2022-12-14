#include "MenuScreen.h"
#include "imgui.h"
#include "UIManager.h"
#include "HierarchyScreen.h"
#include "InspectorScreen.h"
#include "SceneControlsScreen.h"
#include "DebugScreen.h"
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
            if (ImGui::MenuItem("Create Cube..")) { GameObjectManager::get()->createCube(); }
            if (ImGui::MenuItem("Create Plane..")) { GameObjectManager::get()->createPlane(); }
			if (ImGui::MenuItem("Create Sphere..")) { GameObjectManager::get()->createSphere(); }
			if (ImGui::MenuItem("Create Capsule..")) { GameObjectManager::get()->createCapsule(); }
			if (ImGui::MenuItem("Create Static Mesh..")) { InspectorScreen::openFilenameGetter = true; }
            if (ImGui::MenuItem("Save Scene..")) { saveScene(); }
			if (ImGui::MenuItem("Load Scene..")) { loadScene(); }
            ImGui::EndMenu();
        }
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Heirarchy")) { HierarchyScreen::isOpen = true; }
			if (ImGui::MenuItem("Inspector")) { InspectorScreen::isOpen = true; }
			if (ImGui::MenuItem("Scene Controls")) { SceneControlsScreen::isOpen = true; }
			if (ImGui::MenuItem("Debugging Window")) { DebugScreen::isOpen = true; }
			ImGui::EndMenu();
		}
        ImGui::EndMainMenuBar();
    }
}

void MenuScreen::saveScene()
{
	String fileDir = "C:\\Users\\Setiel Olivarez\\Desktop\\School\\GDENG2\\Project\\GDENG-SceneEditor\\Game Engine\\SavedFiles\\" + to_string(1) + ".json";

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

	vector<AGameObject*> allObjects = GameObjectManager::get()->getAllObjects();

	sceneFile << "{" << std::endl;
	sceneFile << "\"primitive\": [" << std::endl;

	for (int i = 0; i < allObjects.size(); i++) {

		sceneFile << "{" << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "\"name\":" << "\" " << allObjects[i]->getName() << " \"," << std::endl;
		sceneFile << "\"type\":" << "\" " << allObjects[i]->type << " \"," << std::endl;

		sceneFile << "\"hasRigidBody\":" << " \"true\" ," << std::endl;

		sceneFile << "\"position\":{\n" << "\"x\": " << position.m_x << " ,\n" << "\"y\": " << position.m_y << " ,\n" << "\"z\": " << position.m_z << "\n }," << std::endl;
		sceneFile << "\"rotation\":{\n" << "\"x\": " << rotation.m_x << " ,\n" << "\"y\": " << rotation.m_y << " ,\n" << "\"z\": " << rotation.m_z << " ,\n" << "\"w\": " << 0 << "\n }," << std::endl;
		sceneFile << "\"scale\":{\n" << "\"x\": " << scale.m_x << " ,\n" << "\"y\": " << scale.m_y << " ,\n" << "\"z\": " << scale.m_z << "\n }" << std::endl;

		if (i < allObjects.size() - 1) {
			sceneFile << "}," << std::endl;
		}
		else {
			sceneFile << "}" << std::endl;
		}
	}
	sceneFile << "] \n}" << std::endl;

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
	String fileDir = "D:\\Academics\\Study References\\DLSU 4th Year - Term 1\\GDENG2\\Final Exam\\Game Engine\\SavedFiles\\" + to_string(1) + ".json";
	//String fileDir = "D:\\Academics\\Study References\\DLSU 4th Year - Term 1\\GDENG2\\Final Exam\\Game Engine\\SavedFiles\\output.json";

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;
	String source = "Editor";

	String objectName;
	String objectType;
	String objectRigidBody;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	if (source == "Editor") {
		while (std::getline(sceneFile, readLine)) {
			//Spacer
			if (index < 3) {
				index++;
			}
			else if (index == 3) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				//To block last char
				if (stringSplit.size() > 2)
					objectName = stringSplit[1];
				index++;
			}
			else if (index == (4)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				objectType = stringSplit[1];
				index++;
			}
			else if (index == (5)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				objectRigidBody = stringSplit[1];
				index++;
			}
			//Spacer
			else if (index < (7)) {
				index++;
			}
			//Position
			else if (index == (7)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (8)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (9)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				position.m_z = std::stof(stringSplit[1]);
				index++;
			}
			//Spacer
			else if (index < (12)) {
				index++;
			}
			//Rotation
			else if (index == (12)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (13)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (14)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				rotation.m_z = std::stof(stringSplit[1]);
				index++;
			}
			//Spacer
			else if (index < (18)) {
				index++;
			}
			//Scale
			else if (index == (18)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_x = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (19)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_y = std::stof(stringSplit[1]);
				index++;
			}
			else if (index == (20)) {
				std::vector<std::string> stringSplit = split(readLine, ' ');
				scale.m_z = std::stof(stringSplit[1]);
				index = 0;
				GameObjectManager::get()->createObjectFromFile(objectName, objectType, position, rotation, scale);
			}
		}
	}
}
/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/AScene.h"

SimplexEngine::Scenes::AScene::AScene(SCENE_PARAMETERS) :
	m_window(p_window),
	m_eventHandler(p_eventHandler),
	m_userInterface(p_userInterface),
	m_inputManager(p_inputManager),
	m_meshManager(p_meshManager)
{
}

void SimplexEngine::Scenes::AScene::Load()
{
	OnLoad();
}

void SimplexEngine::Scenes::AScene::Unload()
{
	OnUnload();
	m_actors.clear();
	m_scripts.clear();
}

const std::vector<std::unique_ptr<SimplexEngine::Scripts::IScript>>& SimplexEngine::Scenes::AScene::GetScripts() const
{
	return m_scripts;
}

const std::vector<std::unique_ptr<SimplexEngine::Actors::Actor>>& SimplexEngine::Scenes::AScene::GetActors() const
{
	return m_actors;
}
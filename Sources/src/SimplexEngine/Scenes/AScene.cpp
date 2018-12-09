/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/AScene.h"

SimplexEngine::Scenes::AScene::AScene(Core::Window& p_window, Core::EventHandler& p_eventHandler, Core::InputManager& p_inputManager, Rendering::Renderer& p_renderer, Core::UserInterface& p_userInterface, Rendering::Rasterizer& p_rasterBoy, Analytics::Profiler& p_profiler, Utils::Clock& p_clock, Resources::Managers::MeshManager& p_meshManager) :
	m_window(p_window),
	m_eventHandler(p_eventHandler),
	m_inputManager(p_inputManager),
	m_renderer(p_renderer),
	m_userInterface(p_userInterface),
	m_rasterBoy(p_rasterBoy),
	m_profiler(p_profiler),
	m_clock(p_clock),
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
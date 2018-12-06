/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scenes/AScene.h"

Rasterizer::Scenes::AScene::AScene(Core::Window & p_window, Core::EventHandler & p_eventHandler, Core::InputManager & p_inputManager, Core::Renderer & p_renderer, Core::UserInterface & p_userInterface, Core::RasterBoy & p_rasterBoy, Analytics::Profiler & p_profiler, Utils::Clock & p_clock, Resources::Managers::MeshManager & p_meshManager) :
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

void Rasterizer::Scenes::AScene::Initialize()
{
	CreateCameras();
	CreateModels();
	CreateScripts();
	DefineParents();
}

std::vector<std::unique_ptr<Rasterizer::Scripts::IScript>>& Rasterizer::Scenes::AScene::GetScripts()
{
	return m_scripts;
}

void Rasterizer::Scenes::AScene::SetAsMainCamera(Entities::Camera & p_camera)
{
	m_mainCamera = &p_camera;
}

std::vector<Rasterizer::Entities::Model>& Rasterizer::Scenes::AScene::GetModels()
{
	return m_models;
}

Rasterizer::Entities::Camera * Rasterizer::Scenes::AScene::GetMainCamera()
{
	return m_mainCamera;
}

std::vector<Rasterizer::Entities::Camera>& Rasterizer::Scenes::AScene::GetCameras()
{
	return m_cameras;
}

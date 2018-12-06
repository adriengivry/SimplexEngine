/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scenes/TestScene.h"
#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Scripts/SRasterizationLimiter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scenes::TestScene::TestScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST
{
}

void Rasterizer::Scenes::TestScene::CreateCameras()
{
	AddCamera(glm::vec3(0.0f, 0.0f, 20.0f), glm::quat(), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
}

void Rasterizer::Scenes::TestScene::CreateModels()
{
	AddModel(*m_meshManager.RequireAndGet("Cube"), glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void Rasterizer::Scenes::TestScene::CreateScripts()
{
	AddScript<Scripts::SCameraController>(m_inputManager, m_cameras[0]);
	AddScript<Scripts::SRasterizationLimiter>(m_rasterBoy, Utils::IniIndexer::Application->Get<float>("rasterization_limiter_speed"));
}

void Rasterizer::Scenes::TestScene::DefineParents()
{
}

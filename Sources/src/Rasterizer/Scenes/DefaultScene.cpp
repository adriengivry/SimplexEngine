/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scenes/DefaultScene.h"

#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Scripts/SRotateOverTime.h"
#include "Rasterizer/Scripts/SRasterizationLimiter.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Utils/Math.h"

Rasterizer::Scenes::DefaultScene::DefaultScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST
{
}

void Rasterizer::Scenes::DefaultScene::CreateCameras()
{
	AddCamera(glm::vec3(0.0f, 0.0f, 20.0f), glm::quat(), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
}

void Rasterizer::Scenes::DefaultScene::CreateModels()
{
	AddModel(*m_meshManager.RequireAndGet("Icosphere"), glm::vec3(0.0f, 0.0f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 0.0f, 0.0f }), glm::vec3(1.0f));
	AddModel(*m_meshManager.RequireAndGet("Icosphere"), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	AddModel(*m_meshManager.RequireAndGet("Icosphere"), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	AddModel(*m_meshManager.RequireAndGet("Icosphere"), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	AddModel(*m_meshManager.RequireAndGet("Monkey"), glm::vec3(3.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f));
	// AddModel(*m_meshManager.RequireAndGet("Plane"), glm::vec3(0.0f, -2.0f, 0.0f), glm::quat(), glm::vec3(10.0f, 1.0f, 10.0f));
}

void Rasterizer::Scenes::DefaultScene::CreateScripts()
{
	AddScript<Scripts::SRotateOverTime>(m_models[0], 90.0f);
	AddScript<Scripts::SRotateOverTime>(m_models[4], 360.0f);
	AddScript<Scripts::SCameraController>(m_inputManager, m_cameras[0]);
}

void Rasterizer::Scenes::DefaultScene::DefineParents()
{
	m_models[1].SetParent(m_models[0]);
	m_models[2].SetParent(m_models[1]);
	m_models[3].SetParent(m_models[2]);
	m_models[4].SetParent(m_models[0]);
}

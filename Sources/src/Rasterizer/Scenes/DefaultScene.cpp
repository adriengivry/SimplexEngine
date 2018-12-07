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
#include "Rasterizer/Components/MeshComponent.h"
#include "Rasterizer/Components/CameraComponent.h"

Rasterizer::Scenes::DefaultScene::DefaultScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST
{
}

void Rasterizer::Scenes::DefaultScene::OnLoad()
{
	/* Actors creation */
	Actors::Actor& mainCamera = AddActor<Actors::Actor>();
	Actors::Actor& icoSphere = AddActor<Actors::Actor>();

	/* Setting up components */
	icoSphere.AddComponent<Components::MeshComponent>(*m_meshManager.RequireAndGet("Icosphere"));
	mainCamera.AddComponent<Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());

	/* Creating scripts */
	Components::CameraComponent& cameraComponent = *mainCamera.GetComponent<Components::CameraComponent>();
	auto test = std::make_unique<Scripts::SCameraController>(m_inputManager, cameraComponent);
	AddScript<Scripts::SCameraController>(m_inputManager, cameraComponent);

	/* Moving actors */
	mainCamera.transform.SetLocalPosition(glm::vec3(0.0f, 0.0f, 20.0f));
}

void Rasterizer::Scenes::DefaultScene::OnUnload()
{
}

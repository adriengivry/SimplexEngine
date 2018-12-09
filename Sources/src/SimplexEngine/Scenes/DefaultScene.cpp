/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/DefaultScene.h"

#include "SimplexEngine/Scripts/SCameraController.h"
#include "SimplexEngine/Scripts/SRotateOverTime.h"
#include "SimplexEngine/Scripts/SRasterizationLimiter.h"
#include "SimplexEngine/Utils/IniIndexer.h"
#include "SimplexEngine/Utils/Math.h"
#include "SimplexEngine/Components/MeshComponent.h"
#include "SimplexEngine/Components/CameraComponent.h"

SimplexEngine::Scenes::DefaultScene::DefaultScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST
{
}

void SimplexEngine::Scenes::DefaultScene::OnLoad()
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

void SimplexEngine::Scenes::DefaultScene::OnUnload()
{
}
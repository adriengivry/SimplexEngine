/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scenes/DefaultScene.h"

#include "SimplexEngine/Scripts/SceneScripts/CameraController.h"
#include "SimplexEngine/Scripts/SceneScripts/RotateOverTime.h"
#include "SimplexEngine/Utils/IniIndexer.h"
#include "SimplexEngine/Components/MeshComponent.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Materials/NormalMaterial.h"

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
	auto test = std::make_unique<Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent);
	AddScript<Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent);

	/* Moving actors */
	mainCamera.transform.SetLocalPosition(glm::vec3(0.0f, 0.0f, 20.0f));
}

void SimplexEngine::Scenes::DefaultScene::OnUnload()
{
}

/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scenes/DemoScene.h"

void Example::Scenes::DemoScene::OnLoad()
{
	auto& cameraActor = AddActor<SimplexEngine::Actors::Actor>();
	auto& cameraComponent = cameraActor.AddComponent<SimplexEngine::Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	cameraActor.transform.SetLocalPosition({ 0.0f, 0.0f, 10.0f });

	auto& icoSphere = AddActor<SimplexEngine::Actors::Actor>();
	icoSphere.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Icosphere"));

	AddScript<SimplexEngine::Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent);
}

void Example::Scenes::DemoScene::OnUnload()
{
}

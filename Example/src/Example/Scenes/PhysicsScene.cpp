/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scenes/PhysicsScene.h"

void Example::Scenes::PhysicsScene::OnLoad()
{
	/* Create the camera */
	auto& cameraActor = AddActor<SimplexEngine::Actors::Actor>();
	auto& cameraComponent = cameraActor.AddComponent<SimplexEngine::Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	cameraActor.transform.SetLocalPosition({ 0.0f, 12.0f, 50.0f });

	/* Floor */
	auto& floorActor = AddActor<SimplexEngine::Actors::Actor>();
	floorActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Cube")).DefineMaterial<SimplexEngine::Materials::DefaultMaterial<SimplexEngine::Shaders::LambertShader>>();
	floorActor.transform.SetLocalPosition({ 0.0f, -2.0f, 0.0f });
	floorActor.transform.SetLocalScale({ 10.0f, 1.0f, 10.0f });
	floorActor.AddComponent<SimplexEngine::Components::BoxColliderComponent>(glm::vec3(10.0f, 1.0f, 10.0f));
	floorActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(0.0f);

	/* Cube */
	for (auto i = 0; i < 10; ++i)
	{
		auto& cubeActor = AddActor<SimplexEngine::Actors::Actor>();
		cubeActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Cube")).DefineMaterial<SimplexEngine::Materials::LambertMaterial>();
		cubeActor.transform.SetLocalPosition({ 0.0f, 20.0f + static_cast<float>(i), 0.0f });
		cubeActor.transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
		cubeActor.AddComponent<SimplexEngine::Components::BoxColliderComponent>(glm::vec3(1.0f, 1.0f, 1.0f));
		cubeActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(10.0f);
	}

	/* Add scripts */
	AddScript<SimplexEngine::Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent, 20.0f, 1.0f);
}

void Example::Scenes::PhysicsScene::OnUnload()
{
}

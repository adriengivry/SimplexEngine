/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scenes/SandboxScene.h"

void Example::Scenes::SandboxScene::OnLoad()
{
	/* Create the camera */
	auto& cameraActor = AddActor<SimplexEngine::Actors::Actor>();
	auto& cameraComponent = cameraActor.AddComponent<SimplexEngine::Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	cameraActor.transform.SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	AddScript<SimplexEngine::Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent, 20.0f, 1.0f);

	auto& gun = AddActor<SimplexEngine::Actors::Actor>();
	gun.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Gun")).DefineMaterial<SimplexEngine::Materials::LambertMaterial>();
	gun.transform.SetLocalPosition({ 1.0f, -0.9f, -3.0f });
	gun.transform.SetLocalRotation(SimplexEngine::Maths::QuaternionFactory::CreateFromEuler({ 90.0f, 0.0f, 0.0f }));
	gun.transform.SetLocalScale(glm::vec3(0.1f));
	gun.transform.SetParent(cameraActor.transform);

	auto& model = AddActor<SimplexEngine::Actors::Actor>();
	model.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Statue")).DefineMaterial<SimplexEngine::Materials::LambertMaterial>();
	model.transform.SetLocalScale(glm::vec3(0.05f));
	model.transform.SetLocalRotation(SimplexEngine::Maths::QuaternionFactory::CreateFromEuler({ 90.0f, 0.0f, 0.0f }));
}

void Example::Scenes::SandboxScene::OnUnload()
{
}

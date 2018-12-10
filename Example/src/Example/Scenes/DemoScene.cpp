/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scenes/DemoScene.h"

void Example::Scenes::DemoScene::OnLoad()
{
	/* Create the camera */
	auto& cameraActor = AddActor<SimplexEngine::Actors::Actor>();
	auto& cameraComponent = cameraActor.AddComponent<SimplexEngine::Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	cameraActor.transform.SetLocalPosition({ 0.0f, 0.0f, 10.0f });

	/* Lambert ico sphere */
	auto& icoSphere = AddActor<SimplexEngine::Actors::Actor>();
	icoSphere.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Icosphere")).DefineMaterial<SimplexEngine::Materials::LambertMaterial>();

	/* Normals ico sphere */
	auto& secondIcoSphere = AddActor<SimplexEngine::Actors::Actor>();
	secondIcoSphere.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Icosphere")).DefineMaterial<SimplexEngine::Materials::NormalMaterial>();
	secondIcoSphere.transform.SetLocalScale(glm::vec3(0.5f));
	secondIcoSphere.transform.SetLocalPosition({ 2.0f, 0.0f, 0.0f });

	SimplexEngine::Actors::Actor* previousActor = nullptr;

	for (uint8_t i = 0; i < 10; ++i)
	{
		auto& newActor = AddActor<SimplexEngine::Actors::Actor>();
		auto& newMesh = newActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Icosphere"));
		newMesh.DefineMaterial<SimplexEngine::Materials::NormalMaterial>();
		newActor.transform.SetLocalPosition({ 0.0f, 1.0f + (previousActor ? 0.0f : 1.0f), 0.0f });
		newActor.transform.SetLocalScale(glm::vec3(0.75));

		if (previousActor)
			newActor.transform.SetParent(previousActor->transform);

		previousActor = &newActor;
	}

	/* Define parent/child relations */
	secondIcoSphere.transform.SetParent(icoSphere.transform);

	/* Add scripts */
	AddScript<SimplexEngine::Scripts::SceneScripts::CameraController>(m_inputManager, cameraComponent, 20.0f, 1.0f);
	AddScript<SimplexEngine::Scripts::SceneScripts::RotateOverTime>(icoSphere, 90.0f);
}

void Example::Scenes::DemoScene::OnUnload()
{
}

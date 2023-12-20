/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scenes/PhysicsScene.h"
#include "Example/Scripts/KillOnFall.h"

void Example::Scenes::PhysicsScene::OnLoad()
{
	/* Create the camera */
	auto& cameraActor = AddActor<SimplexEngine::Actors::Actor>();
	auto& cameraComponent = cameraActor.AddComponent<SimplexEngine::Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	cameraActor.transform.SetLocalPosition({ 0.0f, 50.0f, 0.0f });
	cameraActor.AddComponent<SimplexEngine::Components::CapsuleColliderComponent>(1.0f, 5.0f);
	cameraActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(1.0f);
	cameraActor.AddBehaviour<SimplexEngine::Scripts::Behaviours::FPSController>(m_inputManager, 10.0f, 12.0f);

	/* Floor */
	for (int16_t z = 0; z < 10; z += 1)
	{
		auto& floorActor = AddActor<SimplexEngine::Actors::Actor>();
		auto& floorMeshComp = floorActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Cube"));
		auto& floorMaterial = floorMeshComp.USE_SHADER(SimplexEngine::Shaders::LambertShader);
		floorMaterial.baseColor = SimplexEngine::Data::Color::Red;
		floorActor.transform.SetLocalPosition({ sin(z) * 2.0f, -2.0f, - (z * 10.0f) });
		floorActor.transform.SetLocalScale({ 2.5f, 0.5f, 2.5f });
		floorActor.AddComponent<SimplexEngine::Components::BoxColliderComponent>(glm::vec3(2.5f, 0.5f, 2.5f));
		floorActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(0.0f);

		if (z == 9)
		{
			auto& statue = AddActor<SimplexEngine::Actors::Actor>();
			auto& statueMeshComp = statue.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Statue"));
			auto& statueMaterial = statueMeshComp.USE_SHADER(SimplexEngine::Shaders::LambertShader);
			statueMaterial.baseColor = SimplexEngine::Data::Color(185, 122, 87);
			statue.transform.SetLocalPosition({ sin(z) * 2.0f, 3.5f, -(z * 10.0f) });
			statue.transform.SetLocalScale(glm::vec3(0.05f));
			statue.transform.SetLocalRotation(SimplexEngine::Maths::QuaternionFactory::CreateFromEuler({ 90.0f, 0.0f, 0.0f }));
		}
	}

	auto& gun = AddActor<SimplexEngine::Actors::Actor>();
	auto& gunMeshComp = gun.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Gun"));
	auto& gunMaterial = gunMeshComp.DefineMaterial<SimplexEngine::Materials::DefaultMaterial<SimplexEngine::Shaders::LambertShader>>();
	gunMaterial.baseColor = SimplexEngine::Data::Color(0, 111, 232, 128);
	gun.transform.SetLocalPosition({ 1.0f, -0.9f, -3.0f });
	gun.transform.SetLocalRotation(SimplexEngine::Maths::QuaternionFactory::CreateFromEuler({ 90.0f, 0.0f, 0.0f }));
	gun.transform.SetLocalScale(glm::vec3(0.1f));
	gun.transform.SetParent(cameraActor.transform);

	m_physicsManager.SetGravity(glm::vec3(0.0f, -25.0f, 0.0f));
}

void Example::Scenes::PhysicsScene::OnUnload()
{
}

void Example::Scenes::PhysicsScene::Update(float p_deltaTime)
{
	if (m_inputManager.IsKeyDown(SimplexEngine::Inputs::EKey::KEY_1))
	{
		auto& cubeActor = AddActor<SimplexEngine::Actors::Actor>();
		auto& cubeMeshComp = cubeActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Cube"));
		auto& cubeMaterial = cubeMeshComp.USE_SHADER(SimplexEngine::Shaders::LambertShader);
		cubeMaterial.baseColor = SimplexEngine::Data::Color(m_colorRange(m_randEngine), m_colorRange(m_randEngine), m_colorRange(m_randEngine));
		cubeActor.transform.SetLocalPosition({ 0.0f, 20.0f, -40.0f });
		cubeActor.transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
		cubeActor.AddComponent<SimplexEngine::Components::BoxColliderComponent>(glm::vec3(1.0f, 1.0f, 1.0f));
		cubeActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(10.0f);
		cubeActor.AddBehaviour<Example::Scripts::KillOnFall>(-20.0f);
	}

	if (m_inputManager.IsKeyDown(SimplexEngine::Inputs::EKey::KEY_2))
	{
		auto& sphereActor = AddActor<SimplexEngine::Actors::Actor>();
		auto& sphereMeshComp = sphereActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Sphere"));
		auto& sphereMaterial = sphereMeshComp.USE_SHADER(SimplexEngine::Shaders::LambertShader);
		sphereMaterial.baseColor = SimplexEngine::Data::Color(m_colorRange(m_randEngine), m_colorRange(m_randEngine), m_colorRange(m_randEngine));
		sphereActor.transform.SetLocalPosition({ 0.0f, 20.0f, -40.0f });
		sphereActor.transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
		sphereActor.AddComponent<SimplexEngine::Components::SphereColliderComponent>(1.0f);
		sphereActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(10.0f);
		sphereActor.AddBehaviour<Example::Scripts::KillOnFall>(-20.0f);
	}

	if (m_inputManager.IsKeyDown(SimplexEngine::Inputs::EKey::KEY_3))
	{
		auto& capsuleActor = AddActor<SimplexEngine::Actors::Actor>();
		auto& capsuleMeshComp = capsuleActor.AddComponent<SimplexEngine::Components::MeshComponent>(*m_meshManager.RequireAndGet("Sphere"));
		auto& capsuleMaterial = capsuleMeshComp.USE_SHADER(SimplexEngine::Shaders::LambertShader);
		capsuleMaterial.baseColor = SimplexEngine::Data::Color(m_colorRange(m_randEngine), m_colorRange(m_randEngine), m_colorRange(m_randEngine));
		capsuleActor.transform.SetLocalPosition({ 0.0f, 20.0f, -40.0f });
		capsuleActor.transform.SetLocalScale({ 1.0f, 2.0f, 1.0f });
		capsuleActor.AddComponent<SimplexEngine::Components::CapsuleColliderComponent>(1.0f, 2.0f);
		capsuleActor.AddComponent<SimplexEngine::Components::RigidbodyComponent>(10.0f);
		capsuleActor.AddBehaviour<Example::Scripts::KillOnFall>(-20.0f);
	}
}

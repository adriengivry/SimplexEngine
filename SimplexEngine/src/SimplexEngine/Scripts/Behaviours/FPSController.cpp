/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/Behaviours/FPSController.h"
#include "SimplexEngine/Maths/QuaternionFactory.h"
#include "SimplexEngine/Actors/Actor.h"

SimplexEngine::Scripts::Behaviours::FPSController::FPSController(Actors::Actor& p_owner, const Inputs::InputManager & p_inputManager, float p_movementSpeed, float p_jumpStrength, float p_mouseSensitivity) :
	m_inputManager(p_inputManager),
	m_cameraComponent(*p_owner.GetComponent<Components::CameraComponent>()),
	m_rigidbodyComponent(*p_owner.GetComponent<Components::RigidbodyComponent>()),
	m_mouseSensitivity(p_mouseSensitivity),
	m_movementSpeed(p_movementSpeed),
	m_jumpStrength(p_jumpStrength),
	ABehaviour(p_owner)
{
	m_inputManager.LockMouse();

	m_rigidbodyComponent.GetBody()->setAngularFactor(btVector3(0, 0, 0));
	// m_rigidbodyComponent.GetBody()->setCollisionFlags(m_rigidbodyComponent.GetBody()->getCollisionFlags() | btCollisionObject::CF_CHARACTER_OBJECT);
}

void SimplexEngine::Scripts::Behaviours::FPSController::Update(float p_deltaTime)
{
	if (m_inputManager.IsMouseLocked())
		HandleMouse(p_deltaTime);

	HandleKeyboard(p_deltaTime);
}

void SimplexEngine::Scripts::Behaviours::FPSController::HandleMouse(float p_deltaTime)
{
	auto[motionX, motionY] = m_inputManager.GetMouseMotion();

	/* Prevent very big movement to get applied (These movement are usually caused by alt tab, gaining focus */
	if (std::abs(motionX) + std::abs(motionY) > 100.0f)
		return;

	const float xOffset = motionX * m_mouseSensitivity;
	const float yOffset = motionY * m_mouseSensitivity;

	/* The yaw is influenced by x movements of the mouse */
	m_yaw -= xOffset;
	m_pitch -= yOffset;

	/* We prevent the camera from doing a barrel roll */
	if (m_pitch <= -89.0f)
		m_pitch = -89.0f;
	if (m_pitch >= 89.0f)
		m_pitch = 89.0f;

	m_cameraComponent.owner->transform.SetLocalRotation(Maths::QuaternionFactory::CreateFromEuler({ m_pitch, m_yaw, 0.0f }));
}

void SimplexEngine::Scripts::Behaviours::FPSController::HandleKeyboard(float p_deltaTime)
{
	glm::vec3 movement(0.0f, 0.0f, 0.0f);

	glm::vec3 forward = glm::normalize(m_cameraComponent.GetForward() * glm::vec3(1.0f, 0.0f, 1.0f)); /* Scale Y to 0 to keep only X and Z (Fake forward) */
	glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0, 0.0f));

	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_A))
		movement -= right;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_D))
		movement += right;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_S))
		movement -= forward;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_W))
		movement += forward;

	m_rigidbodyComponent.SetVelocity({ movement.x * m_movementSpeed, m_rigidbodyComponent.GetVelocity().y, movement.z * m_movementSpeed });

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_LALT))
		m_inputManager.UnlockMouse();

	if (m_inputManager.HasKeyBeenReleased(Inputs::EKey::KEY_LALT))
		m_inputManager.LockMouse();

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_SPACE))
	{
		m_rigidbodyComponent.GetBody()->clearForces();
		m_rigidbodyComponent.GetBody()->applyCentralImpulse(btVector3(0.0f, 1.0f, 0.0f) * m_jumpStrength);
	}
}

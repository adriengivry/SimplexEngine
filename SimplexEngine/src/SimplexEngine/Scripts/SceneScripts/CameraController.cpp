/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Scripts/SceneScripts/CameraController.h"
#include "SimplexEngine/Maths/QuaternionFactory.h"
#include "SimplexEngine/Actors/Actor.h"

SimplexEngine::Scripts::SceneScripts::CameraController::CameraController(const Inputs::InputManager& p_inputManager, Components::CameraComponent& p_cameraComponent, float p_movementSpeed, float p_mouseSensitivity) :
	m_inputManager(p_inputManager),
	m_cameraComponent(p_cameraComponent),
	m_mouseSensitivity(p_mouseSensitivity),
	m_movementSpeed(p_movementSpeed)
{
	m_inputManager.LockMouse();
}

void SimplexEngine::Scripts::SceneScripts::CameraController::Update(float p_deltaTime)
{
	if (m_inputManager.IsMouseLocked())
		HandleMouse(p_deltaTime);

	HandleKeyboard(p_deltaTime);
}

void SimplexEngine::Scripts::SceneScripts::CameraController::HandleMouse(float p_deltaTime)
{
	auto [motionX, motionY] = m_inputManager.GetMouseMotion();

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

void SimplexEngine::Scripts::SceneScripts::CameraController::HandleKeyboard(float p_deltaTime)
{
	glm::vec3 movement;

	glm::vec3 forward = glm::normalize(m_cameraComponent.GetForward() * glm::vec3(1.0f, 0.0f, 1.0f)); /* Scale Y to 0 to keep only X and Z (Fake forward) */
	glm::vec3 up = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 right = glm::cross(forward, up);

	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_A))
		movement -= right;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_D))
		movement += right;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_S))
		movement -= forward;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_W))
		movement += forward;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_E))
		movement += up;
	if (m_inputManager.IsKeyDown(Inputs::EKey::KEY_Q))
		movement -= up;

	m_cameraComponent.owner->transform.TranslateLocal(movement * m_movementSpeed * p_deltaTime);

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_LALT))
		m_inputManager.UnlockMouse();

	if (m_inputManager.HasKeyBeenReleased(Inputs::EKey::KEY_LALT))
		m_inputManager.LockMouse();
}

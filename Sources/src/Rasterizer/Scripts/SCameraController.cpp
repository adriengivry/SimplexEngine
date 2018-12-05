/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Utils/Math.h"

#include <iostream>

Rasterizer::Scripts::SCameraController::SCameraController(const Core::InputManager& p_inputManager, Entities::Camera& p_camera) :
	m_inputManager(p_inputManager),
	m_camera(p_camera)
{
	m_inputManager.LockMouse();
}

void Rasterizer::Scripts::SCameraController::Update(float p_deltaTime)
{
	if (m_inputManager.IsMouseLocked())
		HandleMouse(p_deltaTime);

	HandleKeyboard(p_deltaTime);
}

void Rasterizer::Scripts::SCameraController::HandleMouse(float p_deltaTime)
{
	auto [motionX, motionY] = m_inputManager.GetMouseMotion();

	/* Prevent very big movement to get applied (These movement are usually caused by alt tab, gaining focus */
	if (std::abs(motionX) + std::abs(motionY) > 100.0f)
		return;

	const float xOffset = motionX * m_mouseSensitivity * p_deltaTime;
	const float yOffset = motionY * m_mouseSensitivity * p_deltaTime;

	/* The yaw is influenced by x movements of the mouse */
	m_yaw -= xOffset;
	m_pitch -= yOffset;

	/* We prevent the camera from doing a barrel roll */
	if (m_pitch <= -89.0f)
		m_pitch = -89.0f;
	if (m_pitch >= 89.0f)
		m_pitch = 89.0f;

	m_camera.transform.SetLocalRotation(Utils::Math::CreateQuaternionFromEuler({ m_pitch, m_yaw, 0.0f }));
}

void Rasterizer::Scripts::SCameraController::HandleKeyboard(float p_deltaTime)
{
	glm::vec3 movement;

	glm::vec3 forward = glm::normalize(m_camera.GetForward() * glm::vec3(1.0f, 0.0f, 1.0f)); /* Scale Y to 0 to keep only X and Z (Fake forward) */
	glm::vec3 up = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 right = glm::cross(forward, up);

	if (m_inputManager.IsKeyDown(SDL_SCANCODE_A))
		movement -= right;
	if (m_inputManager.IsKeyDown(SDL_SCANCODE_D))
		movement += right;
	if (m_inputManager.IsKeyDown(SDL_SCANCODE_S))
		movement -= forward;
	if (m_inputManager.IsKeyDown(SDL_SCANCODE_W))
		movement += forward;
	if (m_inputManager.IsKeyDown(SDL_SCANCODE_E))
		movement += up;
	if (m_inputManager.IsKeyDown(SDL_SCANCODE_Q))
		movement -= up;

	m_camera.transform.TranslateLocal(movement * Utils::IniIndexer::Controls->Get<float>("movement_speed") * p_deltaTime);

	if (m_inputManager.HasKeyBeenPressed(SDL_SCANCODE_LALT))
		m_inputManager.UnlockMouse();

	if (m_inputManager.HasKeyBeenReleased(SDL_SCANCODE_LALT))
		m_inputManager.LockMouse();
}

/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Utils/IniIndexer.h"
#include "Rasterizer/Utils/Math.h"

#include <iostream>

Rasterizer::Scripts::SCameraController::SCameraController(const Context::InputManager & p_inputManager, Entities::Camera & p_camera) :
	m_inputManager(p_inputManager),
	m_camera(p_camera)
{
}

void Rasterizer::Scripts::SCameraController::Update(float p_deltaTime)
{
	HandleMouse(p_deltaTime);
	HandleKeyboard(p_deltaTime);
}

void Rasterizer::Scripts::SCameraController::HandleMouse(float p_deltaTime)
{
	auto [motionX, motionY] = m_inputManager.GetMouseMotion();

	const float xOffset = motionX * m_mouseSensitivity * p_deltaTime;
	const float yOffset = -motionY * m_mouseSensitivity * p_deltaTime;

	m_camera.transform.Rotate(Utils::Math::CreateQuaternionFromEuler({ xOffset, yOffset, 0.0f }));
}

void Rasterizer::Scripts::SCameraController::HandleKeyboard(float p_deltaTime)
{
	glm::vec3 movement;

	glm::vec3 forward = m_camera.GetForward();
	glm::vec3 up = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 right = glm::cross(forward, up);

	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_A))
		movement -= right;
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_D))
		movement += right;
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_S))
		movement -= forward;
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_W))
		movement += forward;
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_E))
		movement += up;
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_Q))
		movement -= up;

	m_camera.transform.Translate(movement * Utils::IniIndexer::Controls->Get<float>("movement_speed") * p_deltaTime);
}

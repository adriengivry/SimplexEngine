/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Utils/IniIndexer.h"

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
}

void Rasterizer::Scripts::SCameraController::HandleKeyboard(float p_deltaTime)
{
	glm::vec3 movement;

	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_A))
		movement += glm::vec3(-1.0f, 0.0f, 0.0f);
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_D))
		movement += glm::vec3(1.0f, 0.0f, 0.0f);
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_W))
		movement += glm::vec3(0.0f, 0.0f, -1.0f);
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_S))
		movement += glm::vec3(0.0f, 0.0f, 1.0f);
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_Q))
		movement += glm::vec3(0.0f, -1.0f, 0.0f);
	if (m_inputManager.IsKeyPressed(SDL_SCANCODE_E))
		movement += glm::vec3(0.0f, 1.0f, 0.0f);

	m_camera.Move(movement * Utils::IniIndexer::Controls->Get<float>("movement_speed") * p_deltaTime);
}

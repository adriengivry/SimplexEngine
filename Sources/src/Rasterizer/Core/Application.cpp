/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>
#include <SDL.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Rasterizer/Core/Application.h"
#include "Rasterizer/Data/Vertex.h"
#include "Rasterizer/Data/Triangle2D.h"
#include "Rasterizer/Utils/Math.h"

Rasterizer::Core::Application::Application() :
	m_window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	m_renderer(m_window),
	m_rasterBoy(m_window, m_camera, m_renderer),
	m_camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio()),
	m_applicationState(EApplicationState::RUNNING)
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());

	m_models.emplace_back(*m_meshManager.RequireAndGet(Utils::IniIndexer::Application->Get<std::string>("default_mesh")), glm::vec3(0.0f, 0.0f, 0.0f), glm::quat());
}

int Rasterizer::Core::Application::Run()
{
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);
		m_inputManager.Update();

		Update(m_clock.GetDeltaTime());

		for (auto& model : m_models)
			m_rasterBoy.RasterizeModel(model);

		m_renderer.GenerateFinalTexture();
		m_renderer.ClearPixelBuffer();
		m_renderer.DrawFinalTexture();

		m_renderer.Render();

		m_clock.Tick();
	}

	return EXIT_SUCCESS;
}

void Rasterizer::Core::Application::Update(float p_deltaTime)
{
	m_logFPStimer += p_deltaTime;

	if (m_logFPStimer >= 0.5f)
	{
		system("CLS");
		std::cout << static_cast<uint16_t>(m_clock.GetFramerate()) << std::endl;
		m_logFPStimer = 0.0f;
	}

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

	glm::quat eulerRotation;
	m_models[0].transform.SetRotation(glm::quat({ 0.0f, m_modelRotation, 0.0f }));
	m_modelRotation += glm::radians(Utils::IniIndexer::Controls->Get<float>("model_rotation_per_second")) * p_deltaTime;
}

bool Rasterizer::Core::Application::IsRunning()
{
	return m_applicationState == EApplicationState::RUNNING;
}

void Rasterizer::Core::Application::Stop()
{
	m_applicationState = EApplicationState::STOPPED;
}

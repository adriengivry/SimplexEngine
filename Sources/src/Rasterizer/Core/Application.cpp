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
#include "Rasterizer/Scripts/SCameraController.h"
#include "Rasterizer/Scripts/SRotateOverTime.h"
#include "Rasterizer/Scripts/SFPSCounter.h"
#include "Rasterizer/Scripts/SProfilerLogger.h"
#include "Rasterizer/Scripts/SConsoleController.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

Rasterizer::Core::Application::Application() :
	m_window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	m_inputManager(m_eventHandler),
	m_renderer(m_window),
	m_userInterface(m_window, m_renderer),
	m_rasterBoy(m_window, m_camera, m_renderer),
	m_camera({ Utils::IniIndexer::Application->Get<float>("camera_position_x"), Utils::IniIndexer::Application->Get<float>("camera_position_y"), Utils::IniIndexer::Application->Get<float>("camera_position_z")},Utils::Math::CreateQuaternionFromEuler({ Utils::IniIndexer::Application->Get<float>("camera_rotation_x"), Utils::IniIndexer::Application->Get<float>("camera_rotation_y"), Utils::IniIndexer::Application->Get<float>("camera_rotation_z")}), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio()),
	m_applicationState(EApplicationState::RUNNING)
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());

	m_models.emplace_back(*m_meshManager.RequireAndGet(Utils::IniIndexer::Application->Get<std::string>("default_mesh")), glm::vec3(0.0f, 0.0f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 0.0f, 0.0f }), glm::vec3(1.0f));
	m_models.emplace_back(*m_meshManager.RequireAndGet(Utils::IniIndexer::Application->Get<std::string>("default_mesh")), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	m_models.emplace_back(*m_meshManager.RequireAndGet(Utils::IniIndexer::Application->Get<std::string>("default_mesh")), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	m_models.emplace_back(*m_meshManager.RequireAndGet(Utils::IniIndexer::Application->Get<std::string>("default_mesh")), glm::vec3(0.0f, 1.5f, 0.0f), Utils::Math::CreateQuaternionFromEuler({ 0.0, 45.0f, 0.0f }), glm::vec3(0.5f));
	m_models.emplace_back(*m_meshManager.RequireAndGet("Monkey"), glm::vec3(3.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f));

	m_models[1].SetParent(m_models[0]);
	m_models[2].SetParent(m_models[1]);
	m_models[3].SetParent(m_models[2]);
	m_models[4].SetParent(m_models[0]);

	CreateScripts();
}

void Rasterizer::Core::Application::CreateScripts()
{
	AddScript<Scripts::SRotateOverTime>(m_models[0], Utils::IniIndexer::Application->Get<float>("model_rotation_per_second"));
	AddScript<Scripts::SRotateOverTime>(m_models[4], 360.0f);
	AddScript<Scripts::SCameraController>(m_inputManager, m_camera);
	AddScript<Scripts::SConsoleController>(m_inputManager);
	AddScript<Scripts::SFPSCounter>(m_userInterface);
	AddScript<Scripts::SProfilerLogger>(m_profiler, m_inputManager);
}

int Rasterizer::Core::Application::Run()
{
	m_clock.Tick();

	while (m_applicationState == EApplicationState::RUNNING)
	{
		Update(m_clock.GetDeltaTime());
	}

	return EXIT_SUCCESS;
}

void Rasterizer::Core::Application::Update(float p_deltaTime)
{
	/* Events/Inputs */
	m_inputManager.Update();
	m_eventHandler.HandleEvents(m_window);

	/* Update scripts */
	UpdateScripts(p_deltaTime);

	/* Rasterization process */
	RasterizeModels();

	/* Draw order */
	m_renderer.GenerateFinalTexture();
	m_renderer.ClearPixelBuffer();
	m_renderer.DrawFinalTexture();
	m_userInterface.Draw();

	/* Render on screen */
	m_renderer.Render();

	/* Time managment */
	m_clock.Tick();
}

void Rasterizer::Core::Application::UpdateScripts(float p_deltaTime)
{
	PROFILER_SPY("Application::UpdateScripts");

	for (auto& script : m_scripts)
		script->Update(p_deltaTime);
}

void Rasterizer::Core::Application::RasterizeModels()
{
	PROFILER_SPY("Application::RasterizeModels");

	for (auto& model : m_models)
		m_rasterBoy.RasterizeModel(model);
}

bool Rasterizer::Core::Application::IsRunning() const
{
	return m_applicationState == EApplicationState::RUNNING;
}

void Rasterizer::Core::Application::Stop()
{
	m_applicationState = EApplicationState::STOPPED;
}

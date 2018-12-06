/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Application.h"
#include "Rasterizer/Data/Vertex.h"
#include "Rasterizer/Data/Triangle2D.h"
#include "Rasterizer/Utils/Math.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"
#include "Rasterizer/Scenes/DefaultScene.h"
#include "Rasterizer/Scenes/TestScene.h"
#include "Rasterizer/Scripts/SFPSCounter.h"
#include "Rasterizer/Scripts/SProfilerLogger.h"
#include "Rasterizer/Scripts/SConsoleController.h"

Rasterizer::Core::Application::Application() :
	m_window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	m_inputManager(m_eventHandler),
	m_renderer(m_window),
	m_userInterface(m_window, m_renderer),
	m_rasterBoy(m_window, m_renderer),
	m_applicationState(EApplicationState::RUNNING),
	m_defaultCamera(glm::vec3(0.0f, 0.0f, 10.0f), glm::quat(), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio())
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));

	CreateScene();
	CreateGlobalScripts();
}

int Rasterizer::Core::Application::Run()
{
	m_clock.Tick();

	m_scene->Initialize();

	while (m_applicationState == EApplicationState::RUNNING)
		Update(m_clock.GetDeltaTime());

	return EXIT_SUCCESS;
}

void Rasterizer::Core::Application::CreateScene()
{
	m_scene = std::make_unique<Scenes::TestScene>(m_window, m_eventHandler, m_inputManager, m_renderer, m_userInterface, m_rasterBoy, m_profiler, m_clock, m_meshManager);
}

void Rasterizer::Core::Application::CreateGlobalScripts()
{
	AddGlobalScript<Scripts::SConsoleController>(m_inputManager);
	AddGlobalScript<Scripts::SFPSCounter>(m_userInterface);
	AddGlobalScript<Scripts::SProfilerLogger>(m_profiler, m_inputManager, m_userInterface);
}

void Rasterizer::Core::Application::Update(float p_deltaTime)
{
	/* Events/Inputs */
	m_inputManager.Update();
	m_eventHandler.HandleEvents(m_window);

	/* Update scripts */
	UpdateGlobalScripts(p_deltaTime);
	UpdateSceneScripts(p_deltaTime);

	/* Rasterization process */
	m_rasterBoy.ResetRasterizedTrianglesCount();
	m_rasterBoy.ClearBuffers();
	RasterizeModels();
	m_rasterBoy.SendRasterizationOutputBufferToGPU();

	/* Draw order */
	m_renderer.DrawTexture(m_rasterBoy.GetRasterizationOutputBuffer());
	m_userInterface.Draw();

	/* Render on screen */
	m_renderer.Render();

	/* Time managment */
	m_clock.Tick();
}

void Rasterizer::Core::Application::UpdateSceneScripts(float p_deltaTime)
{
	PROFILER_SPY("Application::UpdateSceneScripts");

	for (auto& script : m_scene->GetScripts())
		script->Update(p_deltaTime);
}

void Rasterizer::Core::Application::UpdateGlobalScripts(float p_deltaTime)
{
	PROFILER_SPY("Application::UpdateGlobalScripts");

	for (auto& script : m_globalScripts)
		script->Update(p_deltaTime);
}

void Rasterizer::Core::Application::RasterizeModels()
{
	PROFILER_SPY("Application::RasterizeModels");

	for (auto& model : m_scene->GetModels())
		m_rasterBoy.RasterizeModel(model, m_scene->GetMainCamera() != nullptr ? *m_scene->GetMainCamera() : m_defaultCamera); /* Use the scene main camera or the default camera if there is no camera in scene */
}

bool Rasterizer::Core::Application::IsRunning() const
{
	return m_applicationState == EApplicationState::RUNNING;
}

void Rasterizer::Core::Application::Stop()
{
	m_applicationState = EApplicationState::STOPPED;
}

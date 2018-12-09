/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/Application.h"
#include "SimplexEngine/Data/Vertex.h"
#include "SimplexEngine/Maths/Triangle2D.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Scenes/DefaultScene.h"
#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Scripts/GlobalScripts/SceneNavigator.h"
#include "SimplexEngine/Materials/LambertMaterial.h"
#include "SimplexEngine/Tools/SceneParser.h"

SimplexEngine::Core::Application::Application() :
	m_window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	m_inputManager(m_eventHandler),
	m_renderer(m_window),
	m_userInterface(m_window, m_renderer),
	m_rasterBoy(m_window, m_renderer),
	m_defaultMaterial(std::make_unique<Materials::LambertMaterial>()),
	m_running(true)
{
	m_eventHandler.QuitEvent.AddListener(std::bind(&SimplexEngine::Core::Application::Stop, this));

	CreateScenes();
	CreateGlobalScripts();

	/* Initialize the default camera */
	m_defaultCamera.AddComponent<Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	m_defaultCamera.transform.SetLocalPosition({0.0f, 0.0f, 10.0f});
}

int SimplexEngine::Core::Application::Run()
{
	m_clock.Tick();

	m_sceneManager.LoadScene("Default");

	while (m_running)
		Update(m_clock.GetDeltaTime());

	return EXIT_SUCCESS;
}

void SimplexEngine::Core::Application::CreateScenes()
{
	m_sceneManager.RegisterScene<Scenes::DefaultScene>("Default", m_window, m_inputManager, m_userInterface, m_eventHandler, m_meshManager);
}

void SimplexEngine::Core::Application::CreateGlobalScripts()
{
	AddGlobalScript<Scripts::GlobalScripts::FPSCounter>(m_userInterface);
	AddGlobalScript<Scripts::GlobalScripts::ProfilerLogger>(m_profiler, m_inputManager, m_userInterface);
	AddGlobalScript<Scripts::GlobalScripts::SceneNavigator>(m_sceneManager, m_inputManager);
}

void SimplexEngine::Core::Application::Update(float p_deltaTime)
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
	RasterizeScene();
	m_rasterBoy.SendRasterizationOutputBufferToGPU();

	/* Draw order */
	m_renderer.DrawTextureBufferContent(m_rasterBoy.GetRasterizationOutputBuffer());
	m_userInterface.Draw();

	/* Render on screen */
	m_renderer.Render();

	/* Time managment */
	m_clock.Tick();
}

void SimplexEngine::Core::Application::UpdateSceneScripts(float p_deltaTime)
{
	PROFILER_SPY("Application::UpdateSceneScripts");

	for (auto& script : m_sceneManager.GetCurrentScene()->GetScripts())
		script->Update(p_deltaTime);
}

void SimplexEngine::Core::Application::UpdateGlobalScripts(float p_deltaTime)
{
	PROFILER_SPY("Application::UpdateGlobalScripts");

	for (auto& script : m_globalScripts)
		script->Update(p_deltaTime);
}

void SimplexEngine::Core::Application::RasterizeScene()
{
	PROFILER_SPY("Application::RasterizeScene");

	for (auto meshComponent : Tools::SceneParser::FindMeshes(*m_sceneManager.GetCurrentScene()))
	{
		/* Find camera from scene and the default camera */
		Components::CameraComponent const* sceneMainCamera = Tools::SceneParser::GetMainCamera(*m_sceneManager.GetCurrentScene());
		Components::CameraComponent const* defaultCamera = m_defaultCamera.GetComponent<Components::CameraComponent>().get();

		/* Use the scene main camera or the default camera if there is no camera in scene */
		auto cameraToUse = sceneMainCamera ? sceneMainCamera : (defaultCamera ? defaultCamera : nullptr);

		/* Render only if there is a camera */
		if (cameraToUse)
		{
			m_defaultMaterial->UpdateUniforms(*cameraToUse, meshComponent.get());
			m_rasterBoy.RasterizeMesh(*meshComponent.get().GetMesh(), m_defaultMaterial->GetShaderInstance());
		}
	}
}

bool SimplexEngine::Core::Application::IsRunning() const
{
	return m_running;
}

void SimplexEngine::Core::Application::Stop()
{
	m_running = false;
}

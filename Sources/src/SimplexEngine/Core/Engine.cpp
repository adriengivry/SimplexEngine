/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/Engine.h"
#include "SimplexEngine/Data/Vertex.h"
#include "SimplexEngine/Maths/Triangle2D.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Scenes/DefaultScene.h"
#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Scripts/GlobalScripts/SceneNavigator.h"
#include "SimplexEngine/Materials/LambertMaterial.h"
#include "SimplexEngine/Tools/SceneParser.h"

SimplexEngine::Core::Engine::Engine() :
	m_window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	m_inputManager(m_eventHandler),
	m_renderer(m_window),
	m_userInterface(m_window, m_renderer),
	m_rasterBoy(m_window, m_renderer),
	m_defaultMaterial(std::make_unique<Materials::LambertMaterial>()),
	m_running(true)
{
	m_eventHandler.QuitEvent.AddListener(std::bind(&SimplexEngine::Core::Engine::Stop, this));

	CreateScenes();
	CreateGlobalScripts();

	/* Initialize the default camera */
	m_defaultCamera.AddComponent<Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetAspectRatio());
	m_defaultCamera.transform.SetLocalPosition({0.0f, 0.0f, 10.0f});
}

int SimplexEngine::Core::Engine::Run()
{
	m_clock.Tick();

	m_sceneManager.LoadScene("Default");

	while (m_running)
		Update(m_clock.GetDeltaTime());

	return EXIT_SUCCESS;
}

void SimplexEngine::Core::Engine::CreateScenes()
{
	m_sceneManager.RegisterScene<Scenes::DefaultScene>("Default", m_window, m_inputManager, m_userInterface, m_eventHandler, m_meshManager);
}

void SimplexEngine::Core::Engine::CreateGlobalScripts()
{
	AddGlobalScript<Scripts::GlobalScripts::FPSCounter>(m_userInterface);
	AddGlobalScript<Scripts::GlobalScripts::ProfilerLogger>(m_profiler, m_inputManager, m_userInterface);
	AddGlobalScript<Scripts::GlobalScripts::SceneNavigator>(m_sceneManager, m_inputManager);
}

void SimplexEngine::Core::Engine::Update(float p_deltaTime)
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

void SimplexEngine::Core::Engine::UpdateSceneScripts(float p_deltaTime)
{
	PROFILER_SPY("Engine::UpdateSceneScripts");

	for (auto& script : m_sceneManager.GetCurrentScene()->GetScripts())
		script->Update(p_deltaTime);
}

void SimplexEngine::Core::Engine::UpdateGlobalScripts(float p_deltaTime)
{
	PROFILER_SPY("Engine::UpdateGlobalScripts");

	for (auto& script : m_globalScripts)
		script->Update(p_deltaTime);
}

void SimplexEngine::Core::Engine::RasterizeScene()
{
	PROFILER_SPY("Engine::RasterizeScene");

	for (auto meshComponent : Tools::SceneParser::FindMeshes(*m_sceneManager.GetCurrentScene()))
	{
		/* Find camera from scene and the default camera */
		Components::CameraComponent const* sceneMainCamera = Tools::SceneParser::GetMainCamera(*m_sceneManager.GetCurrentScene());
		Components::CameraComponent const* defaultCamera = m_defaultCamera.GetComponent<Components::CameraComponent>().get();

		/* Use the scene main camera or the default camera if there is no camera in scene */
		auto cameraToUse = sceneMainCamera ? sceneMainCamera : (defaultCamera ? defaultCamera : nullptr);

		/* Pursue rendering only if there is a camera */
		if (cameraToUse)
		{
			/* Find material from mesh and the default material */
			auto meshComponentMaterial = meshComponent.get().GetMaterial();
			auto defaultMaterial = m_defaultMaterial.get();

			/* Use the mesh material the default material if there is no material in the mesh */
			auto materialToUse = meshComponentMaterial ? meshComponentMaterial : (defaultMaterial ? defaultMaterial : nullptr);

			/* Render only if there is a material */
			if (materialToUse)
			{
				materialToUse->UpdateUniforms(*cameraToUse, meshComponent.get());
				m_rasterBoy.RasterizeMesh(*meshComponent.get().GetMesh(), materialToUse->GetShaderInstance());
			}
		}
	}
}

bool SimplexEngine::Core::Engine::IsRunning() const
{
	return m_running;
}

void SimplexEngine::Core::Engine::Stop()
{
	m_running = false;
}

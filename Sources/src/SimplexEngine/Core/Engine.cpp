/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Core/Engine.h"
#include "SimplexEngine/Data/Vertex.h"
#include "SimplexEngine/Maths/Triangle2D.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Scenes/DefaultScene.h"
#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Materials/LambertMaterial.h"
#include "SimplexEngine/Tools/SceneParser.h"

SimplexEngine::Core::Engine::Engine() :
	window(Utils::IniIndexer::Window->Get<std::string>("title"), Utils::IniIndexer::Window->Get<uint16_t>("width"), Utils::IniIndexer::Window->Get<uint16_t>("height")),
	inputManager(eventHandler),
	renderer(window),
	userInterface(window, renderer),
	rasterBoy(window, renderer),
	sceneManager(window, inputManager, userInterface, eventHandler, meshManager),
	m_defaultMaterial(std::make_unique<Materials::LambertMaterial>()),
	m_running(true)
{
	eventHandler.QuitEvent.AddListener(std::bind(&SimplexEngine::Core::Engine::Stop, this));

	/* Initialize the default camera */
	m_defaultCamera.AddComponent<Components::CameraComponent>(glm::vec3(0.0f, 1.0f, 0.0f), window.GetAspectRatio());
	m_defaultCamera.transform.SetLocalPosition({0.0f, 0.0f, 10.0f});
}

void SimplexEngine::Core::Engine::Update()
{
	/* Calculate elapsed time and delta time */
	clock.Tick();

	/* Handle events and inputs */
	inputManager.Update();
	eventHandler.HandleEvents(window);

	/* Update global scripts (Scene-independant) */
	UpdateGlobalScripts(clock.GetDeltaTime());

	/* Scene dependent logic */
	if (sceneManager.HasCurrentScene())
	{
		/* Update scene scripts (Scene-dependant) */
		UpdateSceneScripts(clock.GetDeltaTime());

		/* Rasterization process */
		rasterBoy.ResetRasterizedTrianglesCount();
		rasterBoy.ClearBuffers();
		RasterizeScene();
		rasterBoy.SendRasterizationOutputBufferToGPU();

		/* Draw the result of the rasterization process to the SDL buffer */
		renderer.DrawTextureBufferContent(rasterBoy.GetRasterizationOutputBuffer());
	}

	/* Draw the UI to the SDL buffer */
	userInterface.Draw();

	/* Display SDL buffer content to the screen */
	renderer.Render();
}

bool SimplexEngine::Core::Engine::IsRunning() const
{
	return m_running;
}

void SimplexEngine::Core::Engine::Stop()
{
	m_running = false;
}

void SimplexEngine::Core::Engine::UpdateSceneScripts(float p_deltaTime)
{
	PROFILER_SPY("Engine::UpdateSceneScripts");

	for (auto& script : sceneManager.GetCurrentScene()->GetScripts())
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

	for (auto meshComponent : Tools::SceneParser::FindMeshes(*sceneManager.GetCurrentScene()))
	{
		/* Find camera from scene and the default camera */
		Components::CameraComponent const* sceneMainCamera = Tools::SceneParser::GetMainCamera(*sceneManager.GetCurrentScene());
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
				rasterBoy.RasterizeMesh(*meshComponent.get().GetMesh(), materialToUse->GetShaderInstance());
			}
		}
	}
}
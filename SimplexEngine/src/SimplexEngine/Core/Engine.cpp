/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <thread>

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Core/Engine.h"
#include "SimplexEngine/Data/Vertex.h"
#include "SimplexEngine/Maths/Triangle2D.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Scripts/GlobalScripts/FPSCounter.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Materials/LambertMaterial.h"
#include "SimplexEngine/Tools/SceneParser.h"

SimplexEngine::Core::Engine::Engine(const Settings::EngineSettings& p_engineSettings) :
	window(p_engineSettings.window),
	inputManager(eventHandler),
	renderer(window, p_engineSettings.video),
	userInterface(window, renderer, p_engineSettings.userInterface),
	rasterizer(window, renderer),
	meshManager(p_engineSettings.resources.meshIndexerPath),
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
		rasterizer.ResetRasterizedTrianglesCount();
		rasterizer.ClearBuffers();
		RasterizeScene();
		rasterizer.SendRasterizationOutputBufferToGPU();

		/* Draw the result of the rasterization process to the SDL buffer */
		renderer.DrawTextureBufferContent(rasterizer.GetRasterizationOutputBuffer());
	}

	/* Draw the UI to the SDL buffer */
	userInterface.Draw();

	/* Display SDL buffer content to the screen */
	renderer.Render();

	/* Analytics */
	profiler.Update(clock.GetDeltaTime());
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

	/* Determine which camera to use (Scene camera, default camera or no camera) */
	const Components::CameraComponent* sceneMainCamera = Tools::SceneParser::GetMainCamera(*sceneManager.GetCurrentScene());
	const Components::CameraComponent* defaultCamera = m_defaultCamera.GetComponent<Components::CameraComponent>().get();
	const Components::CameraComponent* cameraToUse = sceneMainCamera ? sceneMainCamera : (defaultCamera ? defaultCamera : nullptr);

	/* Do not render scene if there is no found camera (Scene or default) */
	if (cameraToUse)
	{
		/* Use as much threads as possible */
		uint8_t threadsToUse = threadManager.GetMaximumThread();

		std::vector<std::thread> regionThreads;

		for (uint8_t threadID = 0; threadID < threadsToUse; ++threadID)
			regionThreads.emplace_back(&Engine::RasterizeRegion, this, *cameraToUse, threadID, threadsToUse);

		for (std::thread& thread : regionThreads)
			thread.join();
	}
}

void SimplexEngine::Core::Engine::RasterizeRegion(const Components::CameraComponent& p_cameraToUse, uint32_t p_regionID, uint32_t p_totalRegions)
{
	const std::vector<std::reference_wrapper<const SimplexEngine::Components::MeshComponent>>& meshes = Tools::SceneParser::FindMeshes(*sceneManager.GetCurrentScene());

	for (uint32_t i = p_regionID; i < meshes.size(); i += p_totalRegions)
	{
		std::reference_wrapper<const SimplexEngine::Components::MeshComponent> currentMesh = meshes.at(i);

		/* Determine which material to use (Mesh material, default material or no material) */
		Materials::AMaterial* meshComponentMaterial = currentMesh.get().GetMaterial();
		Materials::AMaterial* defaultMaterial = m_defaultMaterial.get();
		Materials::AMaterial* materialToUse = meshComponentMaterial ? meshComponentMaterial : (defaultMaterial ? defaultMaterial : nullptr);

		/* Render only if there is a material */
		if (materialToUse)
		{
			materialToUse->UpdateUniforms(p_cameraToUse, currentMesh.get());
			rasterizer.RasterizeMesh(*currentMesh.get().GetMesh(), materialToUse->GetShaderInstance());
		}
	}
}
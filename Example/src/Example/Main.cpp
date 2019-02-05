/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#include "Example/Scenes/DemoScene.h"
#include "Example/Scenes/PhysicsScene.h"
#include "Example/Scenes/SandboxScene.h"

int main()
{
	SimplexEngine::Settings::EngineSettings settings = SimplexEngine::Utils::SettingsLoader::LoadEngineSettings("settings.ini");

	SimplexEngine::Core::Engine engine(settings);

	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::FPSCounter>(engine.userInterface, 0.1f);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::ProfilerLogger>(engine.profiler, engine.inputManager, engine.userInterface, 0.1f);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::ThreadCap>(engine.threadManager, engine.inputManager);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::HardwareInfo>(engine.userInterface, engine.threadManager);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector>(engine.rasterizer, engine.inputManager, engine.userInterface, true);

	engine.sceneManager.RegisterScene<Example::Scenes::DemoScene>("Demo");
	engine.sceneManager.RegisterScene<Example::Scenes::PhysicsScene>("Physics");
	engine.sceneManager.RegisterScene<Example::Scenes::SandboxScene>("Sandbox");

	engine.sceneManager.LoadScene("Physics");

	engine.SetClearColor(SimplexEngine::Data::Color(102, 210, 255, 255));

	while (engine.IsRunning())
	{
		engine.Update();
	}

	return EXIT_SUCCESS;
}
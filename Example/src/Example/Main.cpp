/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#include "Example/Scenes/DemoScene.h"

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
	engine.sceneManager.LoadScene("Demo");

	while (engine.IsRunning())
	{
		engine.Update();
	}

	return EXIT_SUCCESS;
}
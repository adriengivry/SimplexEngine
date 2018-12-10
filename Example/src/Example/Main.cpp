/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#include "Example/Scenes/DemoScene.h"

int main()
{
	SimplexEngine::Core::Engine engine;

	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::FPSCounter>(engine.userInterface);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::ProfilerLogger>(engine.profiler, engine.inputManager, engine.userInterface);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::ThreadCap>(engine.threadManager, engine.inputManager);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::HardwareInfo>(engine.userInterface, engine.threadManager);
	engine.AddGlobalScript<SimplexEngine::Scripts::GlobalScripts::RasterizationModeSelector>(engine.rasterBoy, engine.inputManager);

	engine.sceneManager.RegisterScene<Example::Scenes::DemoScene>("Demo");
	engine.sceneManager.LoadScene("Demo");

	while (engine.IsRunning())
	{
		engine.Update();
	}

	return EXIT_SUCCESS;
}
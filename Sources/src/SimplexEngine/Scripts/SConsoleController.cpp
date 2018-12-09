/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SConsoleController.h"
#include "SimplexEngine/Utils/IniIndexer.h"

SimplexEngine::Scripts::SConsoleController::SConsoleController(const Inputs::InputManager & p_inputManager) :
	m_inputManager(p_inputManager)
{
}

void SimplexEngine::Scripts::SConsoleController::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(SDL_SCANCODE_C))
		ClearConsole();
}

void SimplexEngine::Scripts::SConsoleController::ClearConsole()
{
	system("CLS");
}

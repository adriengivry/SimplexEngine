/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SConsoleController.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SConsoleController::SConsoleController(const Context::InputManager & p_inputManager) :
	m_inputManager(p_inputManager)
{
}

void Rasterizer::Scripts::SConsoleController::Update(float p_deltaTime)
{
	if (m_inputManager.IsKeyEventOccured(SDL_SCANCODE_C))
		ClearConsole();
}

void Rasterizer::Scripts::SConsoleController::ClearConsole()
{
	system("CLS");
}

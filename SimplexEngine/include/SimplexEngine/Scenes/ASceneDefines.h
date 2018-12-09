/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ASCENEDEFINES_H
#define _ASCENEDEFINES_H

/**
* This macro simplify child scenes constructors by providing an alias for the default constructor parameters
*/
#define SCENE_PARAMETERS		const SimplexEngine::Windowing::Window&					p_window,\
								const SimplexEngine::Inputs::InputManager&				p_inputManager,\
								SimplexEngine::Rendering::UserInterface&				p_userInterface,\
								SimplexEngine::Eventing::EventHandler&					p_eventHandler,\
								SimplexEngine::Resources::Managers::MeshManager&		p_meshManager\

/**
* This macro simplify child scenes initialization list by providing an alias for the forwarding of scene parameters to AScene class
*/
#define SCENE_INITIALIZATION_LIST AScene(p_window, p_inputManager, p_userInterface, p_eventHandler, p_meshManager)

#endif // _ASCENEDEFINES_H
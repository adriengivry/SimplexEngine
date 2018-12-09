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
#define SCENE_PARAMETERS		SimplexEngine::Core::Window&						p_window,\
								SimplexEngine::Eventing::EventHandler&			p_eventHandler,\
								SimplexEngine::Core::InputManager&					p_inputManager,\
								SimplexEngine::Rendering::Renderer&					p_renderer,\
								SimplexEngine::Rendering::UserInterface&			p_userInterface,\
								SimplexEngine::Rendering::Rasterizer&				p_rasterBoy,\
								SimplexEngine::Analytics::Profiler&					p_profiler,\
								SimplexEngine::Utils::Clock&						p_clock,\
								SimplexEngine::Resources::Managers::MeshManager&	p_meshManager\

/**
* This macro simplify child scenes initialization list by providing an alias for the forwarding of scene parameters to AScene class
*/
#define SCENE_INITIALIZATION_LIST AScene(p_window, p_eventHandler, p_inputManager, p_renderer, p_userInterface, p_rasterBoy, p_profiler, p_clock, p_meshManager)

#endif // _ASCENEDEFINES_H
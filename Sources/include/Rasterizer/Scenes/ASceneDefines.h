/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ASCENEDEFINES_H
#define _ASCENEDEFINES_H

/**
* This macro simplify child scenes constructors by providing an alias for the default constructor parameters
*/
#define SCENE_PARAMETERS		Rasterizer::Core::Window&						p_window,\
								Rasterizer::Core::EventHandler&					p_eventHandler,\
								Rasterizer::Core::InputManager&					p_inputManager,\
								Rasterizer::Core::Renderer&						p_renderer,\
								Rasterizer::Core::UserInterface&				p_userInterface,\
								Rasterizer::Core::RasterBoy&					p_rasterBoy,\
								Rasterizer::Analytics::Profiler&				p_profiler,\
								Rasterizer::Utils::Clock&						p_clock,\
								Rasterizer::Resources::Managers::MeshManager&	p_meshManager\

/**
* This macro simplify child scenes initialization list by providing an alias for the forwarding of scene parameters to AScene class
*/
#define SCENE_INITIALIZATION_LIST AScene(p_window, p_eventHandler, p_inputManager, p_renderer, p_userInterface, p_rasterBoy, p_profiler, p_clock, p_meshManager)

#endif // _ASCENEDEFINES_H
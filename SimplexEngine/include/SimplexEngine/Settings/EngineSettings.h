/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ENGINESETTINGS_H
#define _ENGINESETTINGS_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Settings/WindowSettings.h"
#include "SimplexEngine/Settings/VideoSettings.h"
#include "SimplexEngine/Settings/UserInterfaceSettings.h"
#include "SimplexEngine/Settings/ResourcesSettings.h"

namespace SimplexEngine::Settings
{
	/**
	* Contains engine settings to use for this project
	*/
	struct API_SIMPLEXENGINE EngineSettings final
	{
		Settings::VideoSettings			video;
		Settings::WindowSettings		window;
		Settings::UserInterfaceSettings userInterface;
		Settings::ResourcesSettings		resources;
	};
}

#endif // _RESOURCESSETTINGS_H
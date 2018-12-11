/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _WINDOWSETTINGS_H
#define _WINDOWSETTINGS_H

#include <string>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Settings
{
	/**
	* Contains window settings to use for this project
	*/
	struct API_SIMPLEXENGINE WindowSettings final
	{
		std::string title;
		uint16_t width;
		uint16_t height;

		bool fullScreen = false;
	};
}

#endif // _WINDOWSETTINGS_H
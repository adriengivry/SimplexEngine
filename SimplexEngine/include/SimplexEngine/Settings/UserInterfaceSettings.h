/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _USERINTERFACESETTINGS_H
#define _USERINTERFACESETTINGS_H

#include <string>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Settings
{
	/**
	* Contains resources settings to use for this project
	*/
	struct API_SIMPLEXENGINE UserInterfaceSettings final
	{
		/**
		* The default font path to use in this project
		*/
		std::string defaultFontPath;

		/**
		* The default font size (Normal font size, small and big fonts will scale).
		* This size is scaled with the window size
		*/
		uint32_t defaultFontSize = 24;

		/**
		* Scale the UI with the screen width (Font will get smaller or bigger depending on the screen size)s
		*/
		bool scaleWithScreenWidth = true;
	};
}

#endif // _USERINTERFACESETTINGS_H
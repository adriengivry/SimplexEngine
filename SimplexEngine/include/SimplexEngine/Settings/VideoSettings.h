/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _VIDEOSETTINGS_H
#define _VIDEOSETTINGS_H

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Settings
{
	/**
	* Contains video settings to use for this project
	*/
	struct API_SIMPLEXENGINE VideoSettings final
	{
		bool verticalSync			= false;
		bool hardwareAcceleration	= false;
	};
}

#endif // _VIDEOSETTINGS_H
/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RESOURCESSETTINGS_H
#define _RESOURCESSETTINGS_H

#include <string>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Settings
{
	/**
	* Contains resources settings to use for this project
	*/
	struct API_SIMPLEXENGINE ResourcesSettings final
	{
		/**
		* Location of the meshes indexer file. This file contain a list of every meshes
		* that the mesh manager can use. Every line in this file correspond to a ID/Location pair
		*/
		std::string meshIndexerPath;
	};
}

#endif // _RESOURCESSETTINGS_H
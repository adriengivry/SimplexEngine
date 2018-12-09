/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INIMANAGER_H
#define _INIMANAGER_H

#include <memory>

#include "SimplexEngine/API/Export.h"

namespace GyvrIni::Core { class IniFile; }

namespace SimplexEngine::Utils
{
	/**
	* This struct regroup every ini files for static usage
	*/
	struct API_SIMPLEXENGINE IniIndexer final
	{
		/**
		* Constructor of IniIndexer.
		* Will initialize every ini files
		*/
		IniIndexer();

		static std::unique_ptr<GyvrIni::Core::IniFile> Engine;
		static std::unique_ptr<GyvrIni::Core::IniFile> Window;
		static std::unique_ptr<GyvrIni::Core::IniFile> Rendering;
		static std::unique_ptr<GyvrIni::Core::IniFile> Controls;
	};
}

#endif // _INIMANAGER_H
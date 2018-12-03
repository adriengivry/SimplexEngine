/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INIMANAGER_H
#define _INIMANAGER_H

#include <memory>

#include <GyvrIni/GyvrIni.h>

namespace Rasterizer::Utils
{
	/**
	* This struct regroup every ini files for static usage
	*/
	struct IniIndexer final
	{
		/* Prevent this static class from being instancied */
		IniIndexer() = delete;

		/**
		* Load every ini data into the memory. This must be called before trying to access any ini file
		*/
		static void Initialize();

		static std::unique_ptr<GyvrIni::Core::IniFile> Application;
		static std::unique_ptr<GyvrIni::Core::IniFile> Window;
		static std::unique_ptr<GyvrIni::Core::IniFile> Rendering;
		static std::unique_ptr<GyvrIni::Core::IniFile> Controls;
	};
}

#endif // _INIMANAGER_H
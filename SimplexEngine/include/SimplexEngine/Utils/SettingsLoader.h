/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SETTINGSLOADER_H
#define _SETTINGSLOADER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Settings/EngineSettings.h"
#include "SimplexEngine/Settings/WindowSettings.h"
#include "SimplexEngine/Settings/VideoSettings.h"
#include "SimplexEngine/Settings/UserInterfaceSettings.h"
#include "SimplexEngine/Settings/ResourcesSettings.h"

namespace SimplexEngine::Utils
{
	/**
	* A simple config file loader that store the content of config files into settings data structure
	*/
	class API_SIMPLEXENGINE SettingsLoader final
	{
	public:
		/**
		* Load engine settings from config file
		* @param p_configFilePath
		*/
		static SimplexEngine::Settings::EngineSettings LoadEngineSettings(const std::string& p_configFilePath);

		/**
		* Load window settings from config file
		* @param p_configFilePath
		*/
		static SimplexEngine::Settings::WindowSettings LoadWindowsSettings(const std::string& p_configFilePath);

		/**
		* Load video settings from config file
		* @param p_configFilePath
		*/
		static SimplexEngine::Settings::VideoSettings LoadVideoSettings(const std::string& p_configFilePath);

		/**
		* Load user interface settings from config file
		* @param p_configFilePath
		*/
		static SimplexEngine::Settings::UserInterfaceSettings LoadUserInterfaceSettings(const std::string& p_configFilePath);

		/**
		* Load resources settings from config file
		* @param p_configFilePath
		*/
		static SimplexEngine::Settings::ResourcesSettings LoadResourcesSettings(const std::string& p_configFilePath);
	};
}

#endif // _SETTINGSLOADER_H

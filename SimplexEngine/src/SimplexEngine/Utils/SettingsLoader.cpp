/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Utils/SettingsLoader.h"

SimplexEngine::Settings::EngineSettings SimplexEngine::Utils::SettingsLoader::LoadEngineSettings(const std::string& p_configFilePath)
{
	GyvrIni::Core::IniFile configFile(p_configFilePath);

	Settings::EngineSettings result;

	result.window.title = configFile.Get<std::string>("title");
	result.window.width = configFile.Get<uint16_t>("width");
	result.window.height = configFile.Get<uint16_t>("height");

	result.video.verticalSync = configFile.Get<bool>("vertical_sync");
	result.video.hardwareAcceleration = configFile.Get<bool>("hardware_acceleration");

	result.userInterface.defaultFontPath = configFile.Get<std::string>("default_font_path");
	result.userInterface.defaultFontSize = configFile.Get<uint32_t>("default_font_size");
	result.userInterface.scaleWithScreenWidth = configFile.Get<bool>("scale_with_screen_width");

	result.resources.meshIndexerPath = configFile.Get<std::string>("mesh_indexer_path");

	return result;
}

SimplexEngine::Settings::WindowSettings SimplexEngine::Utils::SettingsLoader::LoadWindowsSettings(const std::string& p_configFilePath)
{
	GyvrIni::Core::IniFile configFile(p_configFilePath);

	Settings::WindowSettings result;

	result.title = configFile.Get<std::string>("title");
	result.width = configFile.Get<uint16_t>("width");
	result.height = configFile.Get<uint16_t>("height");

	return result;
}

SimplexEngine::Settings::VideoSettings SimplexEngine::Utils::SettingsLoader::LoadVideoSettings(const std::string& p_configFilePath)
{
	GyvrIni::Core::IniFile configFile(p_configFilePath);

	Settings::VideoSettings result;

	result.verticalSync = configFile.Get<bool>("vertical_sync");
	result.hardwareAcceleration = configFile.Get<bool>("hardware_acceleration");

	return result;
}

SimplexEngine::Settings::UserInterfaceSettings SimplexEngine::Utils::SettingsLoader::LoadUserInterfaceSettings(const std::string& p_configFilePath)
{
	GyvrIni::Core::IniFile configFile(p_configFilePath);

	Settings::UserInterfaceSettings result;

	result.defaultFontPath = configFile.Get<std::string>("default_font_path");
	result.defaultFontSize = configFile.Get<uint32_t>("default_font_size");
	result.scaleWithScreenWidth = configFile.Get<bool>("scale_with_screen_width");

	return result;
}

SimplexEngine::Settings::ResourcesSettings SimplexEngine::Utils::SettingsLoader::LoadResourcesSettings(const std::string& p_configFilePath)
{
	GyvrIni::Core::IniFile configFile(p_configFilePath);

	Settings::ResourcesSettings result;

	result.meshIndexerPath = configFile.Get<std::string>("mesh_indexer_path");

	return result;
}

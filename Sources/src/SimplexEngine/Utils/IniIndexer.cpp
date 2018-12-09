/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Utils/IniIndexer.h"

std::unique_ptr<GyvrIni::Core::IniFile> SimplexEngine::Utils::IniIndexer::Engine;
std::unique_ptr<GyvrIni::Core::IniFile> SimplexEngine::Utils::IniIndexer::Window;
std::unique_ptr<GyvrIni::Core::IniFile> SimplexEngine::Utils::IniIndexer::Rendering;
std::unique_ptr<GyvrIni::Core::IniFile> SimplexEngine::Utils::IniIndexer::Controls;

SimplexEngine::Utils::IniIndexer::IniIndexer()
{
	Engine = std::make_unique<GyvrIni::Core::IniFile>("config/application.ini");
	Window = std::make_unique<GyvrIni::Core::IniFile>("config/window.ini");
	Rendering = std::make_unique<GyvrIni::Core::IniFile>("config/rendering.ini");
	Controls = std::make_unique<GyvrIni::Core::IniFile>("config/controls.ini");
}

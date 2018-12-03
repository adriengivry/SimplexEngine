/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Utils/IniIndexer.h"

std::unique_ptr<GyvrIni::Core::IniFile> Rasterizer::Utils::IniIndexer::Application;
std::unique_ptr<GyvrIni::Core::IniFile> Rasterizer::Utils::IniIndexer::Window;
std::unique_ptr<GyvrIni::Core::IniFile> Rasterizer::Utils::IniIndexer::Rendering;
std::unique_ptr<GyvrIni::Core::IniFile> Rasterizer::Utils::IniIndexer::Controls;

void Rasterizer::Utils::IniIndexer::Initialize()
{
	Application = std::make_unique<GyvrIni::Core::IniFile>("config/application.ini");
	Window = std::make_unique<GyvrIni::Core::IniFile>("config/window.ini");
	Rendering = std::make_unique<GyvrIni::Core::IniFile>("config/rendering.ini");
	Controls = std::make_unique<GyvrIni::Core::IniFile>("config/controls.ini");
}

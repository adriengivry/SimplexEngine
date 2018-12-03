/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Application.h"

int main()
{
	Rasterizer::Utils::IniIndexer::Initialize();
	Rasterizer::Core::Application app;
	app.Run();
	return 0;
}

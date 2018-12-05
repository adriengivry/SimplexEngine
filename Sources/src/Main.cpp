/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Application.h"

int main(int argc, char* argv[])
{
	Rasterizer::Utils::IniIndexer::Initialize();
	Rasterizer::Core::Application app;
	app.Run();
	return 0;
}

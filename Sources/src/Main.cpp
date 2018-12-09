/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Core/Application.h"

int main(int argc, char* argv[])
{
	SimplexEngine::Utils::IniIndexer::Initialize();
	SimplexEngine::Core::Application app;
	app.Run();
	return 0;
}

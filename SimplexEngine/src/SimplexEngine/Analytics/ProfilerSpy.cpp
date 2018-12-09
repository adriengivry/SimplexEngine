/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Analytics/Profiler.h"

SimplexEngine::Analytics::ProfilerSpy::ProfilerSpy(const std::string & p_name) :
	name(p_name),
	start(std::chrono::steady_clock::now())
{
	
}

SimplexEngine::Analytics::ProfilerSpy::~ProfilerSpy()
{
	end = std::chrono::steady_clock::now();
	SimplexEngine::Analytics::Profiler::Save(*this);
}

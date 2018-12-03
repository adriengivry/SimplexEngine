/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Analytics/ProfilerSpy.h"
#include "Rasterizer/Analytics/Profiler.h"

Rasterizer::Analytics::ProfilerSpy::ProfilerSpy(const std::string & p_name) :
	name(p_name),
	start(std::chrono::steady_clock::now())
{
	
}

Rasterizer::Analytics::ProfilerSpy::~ProfilerSpy()
{
	end = std::chrono::steady_clock::now();
	Rasterizer::Analytics::Profiler::Save(*this);
}

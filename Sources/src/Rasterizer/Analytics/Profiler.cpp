/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include "Rasterizer/Analytics/Profiler.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

std::unordered_map<std::string, double> Rasterizer::Analytics::Profiler::__ELPASED_HISTORY;
std::unordered_map<std::string, uint64_t> Rasterizer::Analytics::Profiler::__CALLS_COUNTER;
bool Rasterizer::Analytics::Profiler::__ENABLED;

Rasterizer::Analytics::Profiler::Profiler()
{
	m_lastTime = std::chrono::high_resolution_clock::now();
	__ENABLED = false;
}

void Rasterizer::Analytics::Profiler::Log()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - m_lastTime;

	std::multimap<double, std::string> sortedHistory;

	std::cout << "---- [Profiler Stats] ----" << std::endl;

	std::cout << "TOTAL ELAPSED TIME: " << elapsed.count() << "s" << std::endl;

	/* Fill the sorted history with the current history (Auto sort) */
	for (auto& data : __ELPASED_HISTORY)
		sortedHistory.insert(std::pair<double, std::string>(data.second, data.first));

	/* Log the history the console */
	for (auto& data : sortedHistory)
	{
		std::string action = data.second;
		std::string duration = std::to_string(data.first) + "s";
		std::string percentage = std::to_string((data.first / elapsed.count()) * 100.0) + "%";
		std::string calls = std::to_string(__CALLS_COUNTER[data.second]);

		std::cout << "METHOD:"			+ action		<< std::endl;
		std::cout << "    DURATION:"	+ duration		<< std::endl;
		std::cout << "    PERCENTAGE:"	+ percentage	<< std::endl;
		std::cout << "    CALLS:"		+ calls			<< std::endl;

		std::cout << std::endl;
	}	
}

Rasterizer::Analytics::ProfilerReport Rasterizer::Analytics::Profiler::GenerateReport()
{
	ProfilerReport report;

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - m_lastTime;

	report.elaspedTime = elapsed.count();

	std::multimap<double, std::string> sortedHistory;

	/* Fill the sorted history with the current history (Auto sort) */
	for (auto& data : __ELPASED_HISTORY)
		sortedHistory.insert(std::pair<double, std::string>(data.second, data.first));

	/* Log the history the console */
	for (auto& data : sortedHistory)
		report.actions.push_back({ data.second, data.first, (data.first / elapsed.count()) * 100.0, __CALLS_COUNTER[data.second] });

	return report;
}

void Rasterizer::Analytics::Profiler::ClearHistory()
{
	__ELPASED_HISTORY.clear();
	__CALLS_COUNTER.clear();

	m_lastTime = std::chrono::high_resolution_clock::now();
}

void Rasterizer::Analytics::Profiler::Save(Rasterizer::Analytics::ProfilerSpy& p_spy)
{
	if (__ELPASED_HISTORY.find(p_spy.name) != __ELPASED_HISTORY.end())
	{
		__ELPASED_HISTORY[p_spy.name] += std::chrono::duration<double>(p_spy.end - p_spy.start).count();
	}
	else
	{
		__ELPASED_HISTORY[p_spy.name] = std::chrono::duration<double>(p_spy.end - p_spy.start).count();
	}

	if (__CALLS_COUNTER.find(p_spy.name) != __CALLS_COUNTER.end())
	{
		++__CALLS_COUNTER[p_spy.name];
	}
	else
	{
		__CALLS_COUNTER[p_spy.name] = 1;
	}
}

bool Rasterizer::Analytics::Profiler::IsEnabled()
{
	return __ENABLED;
}

void Rasterizer::Analytics::Profiler::ToggleEnable()
{
	__ENABLED = !__ENABLED;

	if (__ENABLED)
		std::cout << "PROFILER ENABLED" << std::endl;
	else
		std::cout << "PROFILER DISABLED" << std::endl;
}

void Rasterizer::Analytics::Profiler::Enable()
{
	__ENABLED = true;
}

void Rasterizer::Analytics::Profiler::Disable()
{
	__ENABLED = false;
}

/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include "SimplexEngine/Analytics/Profiler.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

bool SimplexEngine::Analytics::Profiler::__ENABLED;
std::mutex SimplexEngine::Analytics::Profiler::__SAVE_MUTEX;
std::unordered_map<std::string, double> SimplexEngine::Analytics::Profiler::__ELPASED_HISTORY;
std::unordered_map<std::string, uint64_t> SimplexEngine::Analytics::Profiler::__CALLS_COUNTER;

SimplexEngine::Analytics::Profiler::Profiler()
{
	m_lastTime = std::chrono::high_resolution_clock::now();
	__ENABLED = false;
}

void SimplexEngine::Analytics::Profiler::Log()
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

SimplexEngine::Analytics::ProfilerReport SimplexEngine::Analytics::Profiler::GenerateReport()
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

void SimplexEngine::Analytics::Profiler::ClearHistory()
{
	__ELPASED_HISTORY.clear();
	__CALLS_COUNTER.clear();

	m_lastTime = std::chrono::high_resolution_clock::now();
}

void SimplexEngine::Analytics::Profiler::Save(SimplexEngine::Analytics::ProfilerSpy& p_spy)
{
	__SAVE_MUTEX.lock();

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

	__SAVE_MUTEX.unlock();
}

bool SimplexEngine::Analytics::Profiler::IsEnabled()
{
	return __ENABLED;
}

void SimplexEngine::Analytics::Profiler::ToggleEnable()
{
	__ENABLED = !__ENABLED;

	if (__ENABLED)
		std::cout << "PROFILER ENABLED" << std::endl;
	else
		std::cout << "PROFILER DISABLED" << std::endl;
}

void SimplexEngine::Analytics::Profiler::Enable()
{
	__ENABLED = true;
}

void SimplexEngine::Analytics::Profiler::Disable()
{
	__ENABLED = false;
}

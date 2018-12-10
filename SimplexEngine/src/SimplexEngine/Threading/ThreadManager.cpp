/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <algorithm>

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Utils/IniIndexer.h"
#include "SimplexEngine/Threading/ThreadManager.h"

SimplexEngine::Threading::ThreadManager::ThreadManager() :
	m_hardwareThreadCap(std::thread::hardware_concurrency()),
	m_threadCap(Utils::IniIndexer::Engine->Get<uint32_t>("default_thread_cap"))
{
}

uint32_t SimplexEngine::Threading::ThreadManager::GetMaximumThread() const
{
	return std::min(m_threadCap, m_hardwareThreadCap);
}

void SimplexEngine::Threading::ThreadManager::SetThreadCap(uint32_t p_newCap)
{
	if (p_newCap >= 1 && p_newCap <= m_hardwareThreadCap)
		m_threadCap = p_newCap;
}

uint32_t SimplexEngine::Threading::ThreadManager::GetThreadCap() const
{
	return m_threadCap;
}

uint32_t SimplexEngine::Threading::ThreadManager::GetHardwareThreadCap() const
{
	return m_hardwareThreadCap;
}

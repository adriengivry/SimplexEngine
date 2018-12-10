/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/GlobalScripts/ThreadCap.h"

SimplexEngine::Scripts::GlobalScripts::ThreadCap::ThreadCap(Threading::ThreadManager & p_threadManager, Inputs::InputManager& p_inputManager) :
	m_threadManager(p_threadManager),
	m_inputManager(p_inputManager),
	m_currentThreadCap(m_threadManager.GetThreadCap())
{
}

void SimplexEngine::Scripts::GlobalScripts::ThreadCap::Update(float p_deltaTime)
{
	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_Z))
		m_threadManager.SetThreadCap(m_threadManager.GetThreadCap() - 1);

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_X))
		m_threadManager.SetThreadCap(m_threadManager.GetThreadCap() + 1);
}

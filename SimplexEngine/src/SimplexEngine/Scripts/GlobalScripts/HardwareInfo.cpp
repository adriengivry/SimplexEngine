/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/GlobalScripts/HardwareInfo.h"

SimplexEngine::Scripts::GlobalScripts::HardwareInfo::HardwareInfo(Rendering::UserInterface & p_userInterface, Threading::ThreadManager & p_threadManager) :
	m_userInterface(p_userInterface),
	m_threadManager(p_threadManager)
{
}

void SimplexEngine::Scripts::GlobalScripts::HardwareInfo::Update(float p_deltaTime)
{
	ShowHardwareInfo();
}

void SimplexEngine::Scripts::GlobalScripts::HardwareInfo::ShowHardwareInfo()
{
	SimplexEngine::Data::Text text;
	text.content = "Maximum thread count: " + std::to_string(m_threadManager.GetMaximumThread()) + "/" + std::to_string(m_threadManager.GetHardwareThreadCap());
	text.position = m_userInterface.bottomLeftAnchor;
	text.horizontalAlign = SimplexEngine::Data::ETextHorizontalAlignment::ALIGN_LEFT;
	text.verticalAlign = SimplexEngine::Data::ETextVerticalAlignment::ALIGN_BOTTOM;
	text.fontSize = Data::EFontSize::SMALL_FONT;
	m_userInterface.AddText(text);
}

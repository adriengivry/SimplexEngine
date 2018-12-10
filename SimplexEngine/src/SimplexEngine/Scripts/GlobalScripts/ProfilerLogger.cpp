/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <GyvrIni/GyvrIni.h>

#include "SimplexEngine/Analytics/ProfilerSpy.h"
#include "SimplexEngine/Scripts/GlobalScripts/ProfilerLogger.h"
#include "SimplexEngine/Utils/IniIndexer.h"

SimplexEngine::Scripts::GlobalScripts::ProfilerLogger::ProfilerLogger(SimplexEngine::Analytics::Profiler& p_profiler, const Inputs::InputManager& p_inputManager, Rendering::UserInterface& p_userInterface) :
	m_inputManager(p_inputManager),
	m_profiler(p_profiler),
	m_userInterface(p_userInterface),
	m_reportGenerationPaused(false),
	m_logTimer(0.0f)
{
}

void SimplexEngine::Scripts::GlobalScripts::ProfilerLogger::Update(float p_deltaTime)
{
	PROFILER_SPY("SProfilerLogger::Update");

	if (m_profiler.IsEnabled())
	{
		m_logTimer += p_deltaTime;

		if (!m_reportGenerationPaused && m_logTimer >= Utils::IniIndexer::Engine->Get<float>("profiler_log_frequency"))
		{
			m_report = m_profiler.GenerateReport();
			m_profiler.ClearHistory();
			m_logTimer = 0.0f;
		}		

		if (m_report.actions.empty())
		{
			m_userInterface.AddText({ "Collecting data...", m_userInterface.topLeftAnchor, Data::EFontSize::SMALL_FONT, Data::Color::White });
		}
		else
		{
			m_userInterface.AddText({ "Report period duration: " + std::to_string(m_report.elaspedTime) + "s", m_userInterface.topLeftAnchor, Data::EFontSize::SMALL_FONT, Data::Color::White });
			int16_t yOffset = 15;
			for (const auto& action : m_report.actions)
			{
				if (yOffset > m_userInterface.height)
					break;

				ShowAction(action, yOffset);
				yOffset += 15;
			}
		}
	}

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_F1))
	{
		m_profiler.ToggleEnable();
		m_reportGenerationPaused = false;
	}

	if (m_inputManager.HasKeyBeenPressed(Inputs::EKey::KEY_P) && m_profiler.IsEnabled())
	{
		if (m_reportGenerationPaused)
		{
			m_profiler.ClearHistory();
			m_logTimer = 0.0f;
		}

		m_reportGenerationPaused = !m_reportGenerationPaused;
	}
}

void SimplexEngine::Scripts::GlobalScripts::ProfilerLogger::ShowAction(const Analytics::ProfilerReport::Action & p_action, int16_t yOffset)
{
	std::string textContent1 = "[" + p_action.name + "]";
	std::string textContent2 = std::to_string(p_action.duration) + "s (total) | " + std::to_string(p_action.duration / p_action.calls) + "s (per call) | " + std::to_string(p_action.percentage) + "% | " + std::to_string(p_action.calls) + " calls";
	std::pair<int16_t, int16_t> position = m_userInterface.topLeftAnchor;

	Data::Color textColor;

	if (p_action.percentage <= 25.0f)
		textColor = Data::Color::Green;
	else if (p_action.percentage <= 50.0f)
		textColor = Data::Color::Yellow;
	else if (p_action.percentage <= 75.0f)
		textColor = Data::Color(255, 165, 0); /* Orange color */
	else
		textColor = Data::Color::Red;

	position.second += yOffset;

	m_userInterface.AddText({ textContent1, position, Data::EFontSize::SMALL_FONT, textColor });

	position.first += 200;

	m_userInterface.AddText({ textContent2, position, Data::EFontSize::SMALL_FONT, textColor });
}

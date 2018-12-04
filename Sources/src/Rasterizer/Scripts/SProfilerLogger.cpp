/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "Rasterizer/Scripts/SProfilerLogger.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SProfilerLogger::SProfilerLogger(Rasterizer::Analytics::Profiler& p_profiler, const Context::InputManager& p_inputManager, Core::UserInterface& p_userInterface) :
	m_inputManager(p_inputManager),
	m_profiler(p_profiler),
	m_userInterface(p_userInterface),
	m_reportGenerationPaused(false),
	m_logTimer(0.0f)
{
}

void Rasterizer::Scripts::SProfilerLogger::Update(float p_deltaTime)
{
	if (m_profiler.IsEnabled())
	{
		m_logTimer += p_deltaTime;

		if (!m_reportGenerationPaused && m_logTimer >= Utils::IniIndexer::Application->Get<float>("profiler_log_frequency"))
		{
			m_report = m_profiler.GenerateReport();
			m_profiler.ClearHistory();
			m_logTimer = 0.0f;
		}		

		int16_t yOffset = 0;
		for (const auto& action : m_report.actions)
		{
			ShowAction(action, yOffset);
			yOffset += 15;
		}
	}

	if (m_inputManager.IsKeyEventOccured(SDL_SCANCODE_F1))
	{
		m_profiler.ToggleEnable();
		m_reportGenerationPaused = false;
	}

	if (m_inputManager.IsKeyEventOccured(SDL_SCANCODE_P) && m_profiler.IsEnabled())
	{
		if (m_reportGenerationPaused)
		{
			m_profiler.ClearHistory();
			m_logTimer = 0.0f;
		}

		m_reportGenerationPaused = !m_reportGenerationPaused;
	}
}

void Rasterizer::Scripts::SProfilerLogger::ShowAction(const Analytics::ProfilerReport::Action & p_action, int16_t yOffset)
{
	std::string textContent1 = "[" + p_action.name + "]";
	std::string textContent2 = std::to_string(p_action.duration) + "s | " + std::to_string(p_action.percentage) + "% | " + std::to_string(p_action.calls) + " calls";
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

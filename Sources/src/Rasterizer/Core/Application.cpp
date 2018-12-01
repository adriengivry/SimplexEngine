/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Application.h"
#include "Rasterizer/Data/Vertex.h"
#include "Rasterizer/Data/Triangle2D.h"

#include <AltMath/AltMath.h>

Rasterizer::Core::Application::Application() :
	m_windowINI("config/window.ini"),
	m_window(m_windowINI.Get<std::string>("title"), m_windowINI.Get<uint16_t>("width"), m_windowINI.Get<uint16_t>("height")),
	m_renderer(m_window),
	m_applicationState(EApplicationState::RUNNING),
	m_model(m_defaultMesh, AltMath::Vector3f::Zero, AltMath::Quaternion::Identity()),
	m_camera(AltMath::Vector3f(2.5f, 2.5f, 2.0f), AltMath::Quaternion::Identity(), 45.0f, 16.0f / 9.0f, 0.1f, 1000.0f, AltMath::Vector3f::Zero, AltMath::Vector3f(0.0f, 1.0f, 0.0f))
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());

	m_defaultMesh.AddVertex({ 0.0f, 0.0f, 0.0f });
	m_defaultMesh.AddVertex({ 1.0f, 0.0f, 0.0f });
	m_defaultMesh.AddVertex({ 1.0f, 1.0f, 0.0f });
}

int Rasterizer::Core::Application::Run()
{
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);

		auto mesh = m_model.GetPrimaryMesh();
		auto vertices = mesh.GetVertices();

		std::cout << 1.0f / m_clock.GetDeltaTime() << std::endl;

		AltMath::Quaternion eulerRotation;
		eulerRotation.MakeFromEuler({ 0.0f, AltMath::Tools::Utils::ToRadians(m_modelRotation), 0.0f  });
		m_model.transform.SetRotation(eulerRotation);

		m_modelRotation += m_clock.GetDeltaTime() * 90.0f;

		Data::Triangle2D triangle(m_camera, m_model.transform.GetWorldMatrix(), vertices[0], vertices[1], vertices[2]);

		for (uint16_t x = 0; x < 1280; ++x)
		{
			for (uint16_t y = 0; y < 720; ++y)
			{
				if (triangle.IsPointIn(AltMath::Vector2i(x, y)))
					m_renderer.SetPixel(x, y, Data::Color::Red);
			}
		}

		m_renderer.GenerateFinalTexture();
		m_renderer.ClearPixelBuffer();
		m_renderer.DrawFinalTexture();

		m_renderer.Render();

		m_clock.Tick();
	}

	return EXIT_SUCCESS;
}

bool Rasterizer::Core::Application::IsRunning()
{
	return m_applicationState == EApplicationState::RUNNING;
}

void Rasterizer::Core::Application::Stop()
{
	m_applicationState = EApplicationState::STOPPED;
}

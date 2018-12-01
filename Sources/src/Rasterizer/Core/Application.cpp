/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Core/Application.h"

#include <AltMath/AltMath.h>

Rasterizer::Core::Application::Application() :
	m_windowINI("config/window.ini"),
	m_window(m_windowINI.Get<std::string>("title"), m_windowINI.Get<uint16_t>("width"), m_windowINI.Get<uint16_t>("height")),
	m_renderer(m_window),
	m_applicationState(EApplicationState::RUNNING)
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());
}

int Rasterizer::Core::Application::Run()
{
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);

		m_test += 0.016f;

		std::vector<AltMath::Vector3f> vertices
		{
			{0.0f, 0.0f, 0.0f},
			{1.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 0.0f}
		};

		auto pixelContainedIn2DTriangle = [](const AltMath::Vector2f& pt, const AltMath::Vector2f& v1, const AltMath::Vector2f& v2, const AltMath::Vector2f& v3)
		{
			auto area = [](const AltMath::Vector2f& p1, const AltMath::Vector2f& p2, const AltMath::Vector2f& p3)
			{
				return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) * 0.5f);
			};

			float A = area(v1, v2, v3);
			float A1 = area(pt, v2, v3);
			float A2 = area(v1, pt, v3);
			float A3 = area(v1, v2, pt);
			return (A == A1 + A2 + A3);
		};

		// MVP = P * V * M
		/*
		AltMath::Matrix4f perspective = AltMath::Matrix4f::CreatePerspective(45, 16.0f / 9.0f, 1, 1000);
		AltMath::Matrix4f view = AltMath::Matrix4f::CreateView(0, 0, 0, 0, 0, 0, 0, 1, 0);
		AltMath::Matrix4f model = AltMath::Matrix4f::Translation(AltMath::Vector3f(0.0f, 0.0f, 0.0f));
		AltMath::Matrix4f mvp = perspective * view * model;
		AltMath::Vector4f pointA = mvp * AltMath::Vector4f(vertices[0].x, vertices[1].y, vertices[2].z, 1.0f);
		*/

		auto perspectiveProject = [&](const AltMath::Vector3f& p_vertex)
		{
			AltMath::Matrix4f proj = AltMath::Matrix4f::CreatePerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
			AltMath::Matrix4f view = AltMath::Matrix4f::CreateView(2.5f, 2.5f, 2.0f, 0, 0, 0, 0, 1, 0);
			AltMath::Matrix4f model = AltMath::Matrix4f() * AltMath::Matrix4f::RotationOnAxisY(m_test);
			AltMath::Matrix4f mvp = proj * view * model;

			auto toScreen = [](const AltMath::Vector4f& p_vector, float p_width, float p_height)
			{
				const float widthHalf = p_width / 2.0f;
				const float heightHalf = p_height / 2.0f;
				return AltMath::Vector2f(((p_vector.x / 5.0f) + 1) * widthHalf, p_height - ((p_vector.y / 5.0f) + 1) * heightHalf);
			};

			return toScreen(mvp * AltMath::Vector4f(p_vertex), 1280, 720);
		};

		AltMath::Vector2f v0 = perspectiveProject(vertices[0]);
		AltMath::Vector2f v1 = perspectiveProject(vertices[1]);
		AltMath::Vector2f v2 = perspectiveProject(vertices[2]);

		for (uint16_t x = 0; x < 1280; ++x)
		{
			for (uint16_t y = 0; y < 720; ++y)
			{
				if (pixelContainedIn2DTriangle(AltMath::Vector2f(x, y), v0, v1, v2))
					m_renderer.SetPixel(x, y, Data::Color::Red);
			}
		}

		m_renderer.GenerateFinalTexture();
		m_renderer.ClearPixelBuffer();
		m_renderer.DrawFinalTexture();

		m_renderer.Render();
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

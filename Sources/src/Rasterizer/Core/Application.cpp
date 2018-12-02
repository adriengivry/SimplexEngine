/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <thread>

#include <AltMath/AltMath.h>

#include "Rasterizer/Core/Application.h"
#include "Rasterizer/Data/Vertex.h"
#include "Rasterizer/Data/Triangle2D.h"
#include "Rasterizer/Utils/Math.h"

Rasterizer::Core::Application::Application() :
	m_windowINI("config/window.ini"),
	m_applicationINI("config/application.ini"),
	m_window(m_windowINI.Get<std::string>("title"), m_windowINI.Get<uint16_t>("width"), m_windowINI.Get<uint16_t>("height")),
	m_renderer(m_window),
	m_applicationState(EApplicationState::RUNNING),
	m_defaultMesh(m_applicationINI.Get<std::string>("default_mesh")),
	m_model(m_defaultMesh, AltMath::Vector3f::Zero, AltMath::Quaternion::Identity()),
	m_camera(AltMath::Vector3f(2.5f, 2.5f, 5.0f), AltMath::Quaternion::Identity(), 45.0f, 16.0f / 9.0f, 0.1f, 1000.0f, AltMath::Vector3f::Zero, AltMath::Vector3f(0.0f, 1.0f, 0.0f))
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());
}

int Rasterizer::Core::Application::Run()
{
	float logFPStimer = 0.0f;
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);

		logFPStimer += m_clock.GetDeltaTime();

		if (logFPStimer >= 0.5f)
		{
			system("CLS");
			std::cout << static_cast<uint16_t>(m_clock.GetFramerate()) << std::endl;
			logFPStimer = 0.0f;
		}

		AltMath::Quaternion eulerRotation;
		m_model.transform.SetRotation(Utils::Math::CreateQuaternionFromEuler({ 0.0f, m_modelRotation, 0.0f }));
		m_modelRotation += m_clock.GetDeltaTime() * m_applicationINI.Get<float>("model_rotation_per_second");

	
		for (auto mesh : m_model.GetMeshes())
		{
			auto vertices = mesh.get().GetVertices();
			auto indices = mesh.get().GetIndices();

			for (uint32_t i = 0; i < indices.size(); i += 3)
			{
				Data::Vertex& firstVertex = vertices[indices[i]];
				Data::Vertex& secondVertex = vertices[indices[i + 1]];
				Data::Vertex& thirdVertex = vertices[indices[i + 2]];

				Data::Triangle2D triangle(m_camera, m_model.transform.GetWorldMatrix(), firstVertex, secondVertex, thirdVertex);

				auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

				if (xmin > xmax) std::swap(xmin, xmax);
				if (ymin > ymax) std::swap(ymin, ymax);

				for (uint16_t x = xmin; x < xmax; ++x)
				{
					for (uint16_t y = ymin; y < ymax; ++y)
					{
						if (triangle.IsPointInArea(AltMath::Vector2i(x, y)) && x >= 0 && x <= 1280 && y >= 0 && y <= 720)
						{
							Data::Color pixelColor;

							pixelColor.r = static_cast<uint8_t>((firstVertex.normal.x * 0.5f + 0.5f) * 255.0f);
							pixelColor.g = static_cast<uint8_t>((firstVertex.normal.y * 0.5f + 0.5f) * 255.0f);
							pixelColor.b = static_cast<uint8_t>((firstVertex.normal.z * 0.5f + 0.5f) * 255.0f);

							m_renderer.SetPixel(x, y, pixelColor);
						}
					}
				}
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

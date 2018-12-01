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

	m_defaultMesh.AddVertex({0.5, 0.5, -0.5}); //2 0 
	m_defaultMesh.AddVertex({-0.5, 0.5, -0.5}); //3 1
	m_defaultMesh.AddVertex({-0.5, -0.5, -0.5}); //0 2
	m_defaultMesh.AddVertex({0.5, 0.5, -0.5}); //2   3
	m_defaultMesh.AddVertex({-0.5, -0.5, -0.5}); //0  4
	m_defaultMesh.AddVertex({0.5, -0.5, -0.5}); //1  5
	m_defaultMesh.AddVertex({0.5, 0.5, 0.5}); //6     6
	m_defaultMesh.AddVertex({0.5, 0.5, -0.5}); //2   7
	m_defaultMesh.AddVertex({0.5, -0.5, -0.5}); //1      8
	m_defaultMesh.AddVertex({0.5, 0.5, 0.5}); //6     9
	m_defaultMesh.AddVertex({0.5, -0.5, -0.5}); //1      10
	m_defaultMesh.AddVertex({0.5, -0.5, 0.5}); //5    11
	m_defaultMesh.AddVertex({-0.5, 0.5, 0.5}); //7   12
	m_defaultMesh.AddVertex({0.5, 0.5, 0.5}); //6    13
	m_defaultMesh.AddVertex({0.5, -0.5, 0.5}); //5    14
	m_defaultMesh.AddVertex({-0.5, 0.5, 0.5}); //7   15
	m_defaultMesh.AddVertex({0.5, -0.5, 0.5}); //5    16
	m_defaultMesh.AddVertex({-0.5, -0.5, 0.5}); //4  17
	m_defaultMesh.AddVertex({-0.5, 0.5, -0.5}); //3  18
	m_defaultMesh.AddVertex({-0.5, 0.5, 0.5}); //7   19
	m_defaultMesh.AddVertex({-0.5, -0.5, 0.5}); //4  20
	m_defaultMesh.AddVertex({-0.5, 0.5, -0.5}); //3  21
	m_defaultMesh.AddVertex({-0.5, -0.5, 0.5}); //4  22
	m_defaultMesh.AddVertex({-0.5, -0.5, -0.5}); //0  23
	m_defaultMesh.AddVertex({-0.5, 0.5, -0.5}); //3  24
	m_defaultMesh.AddVertex({0.5, 0.5, -0.5}); //2   25
	m_defaultMesh.AddVertex({0.5, 0.5, 0.5}); //6     26
	m_defaultMesh.AddVertex({-0.5, 0.5, -0.5}); //3  27
	m_defaultMesh.AddVertex({0.5, 0.5, 0.5}); //6     28
	m_defaultMesh.AddVertex({-0.5, 0.5, 0.5}); //7   29
	m_defaultMesh.AddVertex({-0.5, -0.5, 0.5}); //4   30
	m_defaultMesh.AddVertex({0.5, -0.5, 0.5}); //5    31
	m_defaultMesh.AddVertex({0.5, -0.5, -0.5}); //1      32
	m_defaultMesh.AddVertex({-0.5, -0.5, 0.5}); //4   33
	m_defaultMesh.AddVertex({0.5, -0.5, -0.5}); //1      34
	m_defaultMesh.AddVertex({-0.5, -0.5, -0.5}); //0  35
}

int Rasterizer::Core::Application::Run()
{
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);

		std::cout << m_clock.GetFramerate() << std::endl;

		AltMath::Quaternion eulerRotation;
		eulerRotation.MakeFromEuler({ 0.0f, AltMath::Tools::Utils::ToRadians(m_modelRotation), 0.0f });
		m_model.transform.SetRotation(eulerRotation);
		m_modelRotation += m_clock.GetDeltaTime() * 90.0f;

		for (auto mesh : m_model.GetMeshes())
		{
			auto vertices = mesh.get().GetVertices();

			for (uint32_t i = 2; i < vertices.size(); i += 3)
			{
				Data::Triangle2D triangle(m_camera, m_model.transform.GetWorldMatrix(), vertices[i - 2], vertices[i - 1], vertices[i]);

				for (uint16_t x = 0; x < 1280; ++x)
				{
					for (uint16_t y = 0; y < 720; ++y)
					{
						if (triangle.IsPointIn(AltMath::Vector2i(x, y)))
							m_renderer.SetPixel(x, y, Data::Color::Red);
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

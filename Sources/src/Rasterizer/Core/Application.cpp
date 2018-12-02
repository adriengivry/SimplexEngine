/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <glm/gtx/quaternion.hpp>

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
	m_monkeyMesh("resources/monkey.fbx"),
	m_cubeMesh("resources/cube.fbx"),
	m_sphereMesh("resources/sphere.fbx"),
	m_icoSphereMesh("resources/icosphere.fbx"),
	m_camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), m_window.GetWidth(), m_window.GetHeight())
{
	m_eventHandler.SDLQuitEvent.AddListener(std::bind(&Rasterizer::Core::Application::Stop, this));
	m_renderer.InitializePixelBufferSize(m_window.GetSize());

	m_models.emplace_back(m_monkeyMesh, glm::vec3(0.0f, 0.0f, 0.0f), glm::quat());
}

int Rasterizer::Core::Application::Run()
{
	while (m_applicationState == EApplicationState::RUNNING)
	{
		m_eventHandler.HandleEvents(m_window);

		Update(m_clock.GetDeltaTime());

		for (auto& model : m_models)
			RasterizeModel(model);

		m_renderer.GenerateFinalTexture();
		m_renderer.ClearPixelBuffer();
		m_renderer.DrawFinalTexture();

		m_renderer.Render();

		m_clock.Tick();
	}

	return EXIT_SUCCESS;
}

void Rasterizer::Core::Application::Update(float p_deltaTime)
{
	m_logFPStimer += p_deltaTime;

	if (m_logFPStimer >= 0.5f)
	{
		system("CLS");
		std::cout << static_cast<uint16_t>(m_clock.GetFramerate()) << std::endl;
		m_logFPStimer = 0.0f;
	}

	glm::quat eulerRotation;
	m_models[0].transform.SetRotation(glm::quat({ -90.0f, m_modelRotation, 0.0f }));
	m_modelRotation += m_clock.GetDeltaTime() * m_applicationINI.Get<float>("model_rotation_per_second") * 3.14f / 180.0f;
}

void Rasterizer::Core::Application::RasterizeModel(const Entities::Model & p_actor)
{
	glm::mat4 mvp = m_camera.GetViewProjectionMatrix() * p_actor.transform.GetWorldMatrix();

	for (auto mesh : p_actor.GetMeshes())
	{
		auto vertices = mesh.get().GetVertices();
		auto indices = mesh.get().GetIndices();

		for (uint32_t i = 0; i < indices.size(); i += 3)
		{
			Data::Vertex& firstVertex = vertices[indices[i]];
			Data::Vertex& secondVertex = vertices[indices[i + 1]];
			Data::Vertex& thirdVertex = vertices[indices[i + 2]];

			glm::vec4 firstVertexPosition = mvp * glm::vec4(firstVertex.position, 1.0f);
			glm::vec4 secondVertexPosition = mvp * glm::vec4(secondVertex.position, 1.0f);
			glm::vec4 thirdVertexPosition = mvp * glm::vec4(thirdVertex.position, 1.0f);

			std::pair<int32_t, int32_t> firstPixelCoordinate = m_camera.ProjectToCameraSpace(firstVertexPosition);
			std::pair<int32_t, int32_t> secondPixelCoordinate = m_camera.ProjectToCameraSpace(secondVertexPosition);
			std::pair<int32_t, int32_t> thirdPixelCoordinate = m_camera.ProjectToCameraSpace(thirdVertexPosition);

			Data::Triangle2D triangle(firstPixelCoordinate, secondPixelCoordinate, thirdPixelCoordinate);

			auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

			if (xmin > xmax) std::swap(xmin, xmax);
			if (ymin > ymax) std::swap(ymin, ymax);

			for (uint16_t x = xmin; x < xmax; ++x)
			{
				for (uint16_t y = ymin; y < ymax; ++y)
				{
					float depth = (firstVertexPosition.z + secondVertexPosition.z + thirdVertexPosition.z) * 0.33333f;

					if (triangle.IsPointInArea({ x, y }) && m_window.IsPointInWindow({ x ,y }) && depth < m_renderer.GetDepth(x, y))
					{
						Data::Color pixelColor;

						pixelColor.r = static_cast<uint8_t>((firstVertex.normal.x * 0.5f + 0.5f) * 255.0f);
						pixelColor.g = static_cast<uint8_t>((firstVertex.normal.y * 0.5f + 0.5f) * 255.0f);
						pixelColor.b = static_cast<uint8_t>((firstVertex.normal.z * 0.5f + 0.5f) * 255.0f);

						m_renderer.SetPixel(x, y, pixelColor);
						m_renderer.SetDepth(x, y, depth);
					}
				}
			}
		}
	}
}

bool Rasterizer::Core::Application::IsRunning()
{
	return m_applicationState == EApplicationState::RUNNING;
}

void Rasterizer::Core::Application::Stop()
{
	m_applicationState = EApplicationState::STOPPED;
}

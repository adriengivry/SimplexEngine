/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RASTERBOY_H
#define _RASTERBOY_H

#include "Rasterizer/Core/Window.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Entities/Camera.h"
#include "Rasterizer/Entities/Model.h"

namespace Rasterizer::Core
{
	/**
	* RasterBoy is the main thing of this project, it will compute rasterization (Conversion from world space to screen)
	*/
	class RasterBoy final
	{
	public:
		/**
		* Constructor of the RasterBoy
		* @param p_window
		* @param p_rendrerer
		*/
		RasterBoy(const Core::Window& p_window, Core::Renderer& p_renderer);

		/**
		* Update rasterizer data (Nothing is rasterized here)
		* This update is essentially used to reset rasterized triangles count
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Rasterize a model to the screen
		* @param p_actor
		* @param p_camera
		*/
		void RasterizeModel(const Entities::Model& p_actor, const Entities::Camera& p_camera);

		/**
		* Rasterize a mesh to the screen
		* @param p_mesh
		* @param p_mvp
		*/
		void RasterizeMesh(const Resources::Mesh& p_mesh, const glm::mat4& p_mvp);

		/**
		* Rasterize a triangle to the screen
		* @param p_vertices
		* @param p_mvp
		*/
		void RasterizeTriangle(std::tuple<Data::Vertex, Data::Vertex, Data::Vertex> p_vertices, const glm::mat4& p_mvp);

		/**
		* Project a point to the screen and calculate his depth buffer
		* @param p_point (In camera space, aka after applying MVP)
		*/
		std::pair<glm::vec2, float> ProjectToPixelCoordinates(const glm::vec3& p_point);

		/**
		* Verify is RasterBoy is allow to rasterize
		*/
		bool CanRasterize();

		/**
		* Use this method to limit/unlimit the triangle rasterization process
		* @param p_enable
		*/
		void LimitTriangleRasterization(bool p_enable);

		/**
		* Defines the maximum number of triangles to rasterize
		* @param p_limit
		*/
		void SetRasterizedTriangleLimit(uint64_t p_limit);

	private:
		const Core::Window& m_window;

		Core::Renderer& m_renderer;

		bool m_limitTriangleRasterization;
		uint64_t m_rasterizedTrianglesLimit;
		uint64_t m_rasterizedTriangles;
	};
}

#endif // _RASTERBOY_H
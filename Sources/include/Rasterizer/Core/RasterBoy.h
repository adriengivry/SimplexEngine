/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RASTERBOY_H
#define _RASTERBOY_H

#include "Rasterizer/Context/Window.h"
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
		* @param p_camera
		* @param p_rendrerer
		*/
		RasterBoy(const Context::Window& p_window, const Entities::Camera& p_camera, Core::Renderer& p_renderer);

		/**
		* Rasterize a model to the screen
		* @param p_actor
		*/
		void RasterizeModel(const Entities::Model& p_actor);

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
		std::pair<glm::ivec2, float> ProjectToPixelCoordinates(const glm::vec3& p_point);

	private:
		const Context::Window& m_window;
		const Entities::Camera& m_camera;

		Core::Renderer& m_renderer;
	};
}

#endif // _RASTERBOY_H
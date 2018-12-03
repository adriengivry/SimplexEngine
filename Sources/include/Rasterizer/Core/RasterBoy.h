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

		/**
		* Project a point to the screen coordinate (From Hansdrien Rasterizer)
		* @param p_point (In camera space, aka after applying MVP)
		* @warning For test ony, it has trouble with Z
		*/
		std::pair<glm::ivec2, float> ProjectToPixelCoordinatesHansdrien(const glm::vec3& p_point);

		/**
		* Process the full process of transformation and rasterization of a vertex
		* @param p_vertexPosition (As given in the obj or fbx file)
		* @param p_vertexTransformations (The model matrix)
		* @warning Doesn't work
		*/
		glm::ivec2 RasterizeVertex(const glm::vec3& p_vertexPosition, const glm::mat4& p_vertexTransformations);

		/**
		* Convert a vertex from local position (As given in obj or fbx file) to world space (Apply model matrix)
		* @param p_vertexPosition (As given in the obj or fbx file)
		* @param p_vertexTransformations (The model matrix)
		* @warning Doesn't work
		*/
		glm::vec3 VertexToWorldSpace(const glm::vec3& p_vertexPosition, const glm::mat4& p_vertexTransformations);

		/**
		* Convert a vertex from world position to camera space
		* @param p_vertexWorldPosition (After MVP applyied)
		* @warning Doesn't work
		*/
		glm::vec3 VertexToCameraSpace(const glm::vec3& p_vertexWorldPosition);

		/**
		* Convert a vertex from camera space to screen space
		* @param p_vertexCameraSpace
		* @warning Doesn't work
		*/
		glm::vec2 VertexToScreenSpace(const glm::vec3& p_vertexCameraSpace);

		/**
		* Convert a vertex from screen space to NDC (Normalized coordinates)
		* @param p_vertexScreenSpace
		* @warning Doesn't work
		*/
		glm::vec2 VertexToNormalizedCoordinates(const glm::vec2& p_vertexScreenSpace);

		/**
		* Convert a vertex from NDC (Normalized coordinates) to raster space (Pixel index on the screen)
		* @param p_vertexNormalizedCoordinates
		* @warning Doesn't work
		*/
		glm::ivec2 VertexToRasterSpace(const glm::vec2& p_vertexNormalizedCoordinates);

	private:
		const Context::Window& m_window;
		const Entities::Camera& m_camera;

		Core::Renderer& m_renderer;
	};
}

#endif // _RASTERBOY_H
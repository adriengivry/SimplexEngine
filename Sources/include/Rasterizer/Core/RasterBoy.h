/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RASTERBOY_H
#define _RASTERBOY_H

#include <array>

#include "Rasterizer/Core/Window.h"
#include "Rasterizer/Core/Renderer.h"
#include "Rasterizer/Buffers/DepthBuffer.h"
#include "Rasterizer/Buffers/TextureBuffer.h"
#include "Rasterizer/Resources/Mesh.h"
#include "Rasterizer/Shaders/AShader.h"

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
		* Reset the rasterized triangle count
		*/
		void ResetRasterizedTrianglesCount();

		/**
		* Clear depth and rasterization buffer
		*/
		void ClearBuffers();

		/**
		* Rasterize a mesh to the screen
		* @param p_mesh
		* @param p_mvp
		* @param p_shader
		*/
		void RasterizeMesh(const Resources::Mesh& p_mesh, Shaders::AShader& p_shader);

		/**
		* Rasterize a triangle to the screen
		* @param p_vertices
		* @param p_mvp
		* @param p_shader
		*/
		void RasterizeTriangle(const std::array<Data::Vertex, 3>& p_vertices, Shaders::AShader& p_shader);

		/**
		* Convert a vertex to raster space
		* @param p_vertex
		*/
		void ConvertToRasterSpace(glm::vec4& p_vertex);

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

		/**
		* Return the result of the rasterization as a 2D buffer (Texture buffer)
		*/
		const Buffers::TextureBuffer& GetRasterizationOutputBuffer() const;

		/**
		* Send the rasterization output buffer to GPU to make it available
		* for future draw (DrawTexture from renderer)
		*/
		void SendRasterizationOutputBufferToGPU();

	private:
		const Core::Window& m_window;

		Core::Renderer& m_renderer;

		Buffers::DepthBuffer m_depthBuffer;
		Buffers::TextureBuffer m_rasterizationOutputBuffer;

		bool m_limitTriangleRasterization;
		uint64_t m_rasterizedTrianglesLimit;
		uint64_t m_rasterizedTriangles;
	};
}

#endif // _RASTERBOY_H
/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RASTERBOY_H
#define _RASTERBOY_H

#include <array>
#include <mutex>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Settings/VideoSettings.h"
#include "SimplexEngine/Rendering/Renderer.h"
#include "SimplexEngine/Rendering/ERasterizationDrawMode.h"
#include "SimplexEngine/Rendering/ERasterizationCullingMode.h"
#include "SimplexEngine/Buffers/DepthBuffer.h"
#include "SimplexEngine/Buffers/TextureBuffer.h"
#include "SimplexEngine/Resources/Mesh.h"
#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Maths/Triangle2D.h"

namespace SimplexEngine::Rendering
{
	/**
	* Rasterizer is the main thing of this project, it will compute rasterization (Conversion from world space to screen)
	*/
	class API_SIMPLEXENGINE Rasterizer final
	{
	public:
		/**
		* Constructor of the Rasterizer
		* @param p_rendrerer (Needed to create the out buffer because it uses SDL Texture)
		* @param p_rasterizationBufferWidth
		* @param p_rasterizationBufferHeight
		*/
		Rasterizer(const Rendering::Renderer& p_renderer, uint16_t p_rasterizationBufferWidth, uint16_t p_rasterizationBufferHeight);

		/**
		* Modify the current rasterization draw mode
		* @param p_drawMode
		*/
		void SetRasterizationDrawMode(ERasterizationDrawMode p_drawMode);

		/**
		* Return the current rasterization draw mode
		*/
		ERasterizationDrawMode GetRasterizationDrawMode();

		/**
		* Modify the current rasterization culling mode
		* @param p_cullingMode
		*/
		void SetRasterizationCullingwMode(ERasterizationCullingMode p_cullingMode);

		/**
		* Return the current rasterization mode
		*/
		ERasterizationCullingMode GetRasterizationCullingMode();

		/**
		* Reset the rasterized triangle count
		*/
		void ResetRasterizedTrianglesCount();

		/**
		* Clear rasterization output and depth buffer
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
		* Rasterize a triangle in wireframe mode (Only line)
		* @param p_triangle
		*/
		void RasterizeTriangleWireframe(const Maths::Triangle2D& p_triangle, const Data::Color& p_color);

		/**
		* Draw a line between the two given points
		* @param p_start
		* @param p_end
		* @param p_color
		*/
		void RasterizeLine(const glm::vec2& p_start, const glm::vec2& p_end, const Data::Color& p_color);

		/**
		* Compute a set of vertices by processing vertex shader on them
		* @param p_vertices
		* @param p_shader
		*/
		std::array<glm::vec4, 3> ComputeVertices(const std::array<Data::Vertex, 3>& p_vertices, Shaders::AShader& p_shader);

		/**
		* Compute fragments by processing fragment shader on every fragment and
		* updating the depth and pixel buffer
		* @param p_pixelCoordinates
		* @param p_depth
		* @param p_shader
		*/
		void ComputeFragments(Shaders::AShader& p_shader, const std::array<glm::vec4, 3>& p_transformedVertices, Maths::Triangle2D& p_triangle);

		/**
		* Compute a fragment by processing fragment shader calculation and
		* updating the depth and pixel buffer
		* @param p_pixelCoordinates
		* @param p_depth
		* @param p_shader
		*/
		void ComputeFragment(const std::pair<int32_t, int32_t>& p_pixelCoordinates, float p_depth, const glm::vec3& p_barycentricCoordinates, Shaders::AShader& p_shader);

		/**
		* Convert a vertex to raster space
		* @param p_vertex
		*/
		void ConvertToRasterSpace(glm::vec4& p_vertex) const;

		/**
		* Verify if barycentric coords are valid (If the pixel expressed in barycentric coordinates is triangle bounds)
		* @param p_barycentricCoords
		*/
		bool BarycentricCoordsAreValid(const glm::vec3& p_barycentricCoords) const;

		/**
		* Calculate the "depth" of a point in screen space using barycentric coordinates
		* to interpolate the depth of every vertices to find the actual depth of the point
		* @param p_vertices
		* @param p_barycentricCoords (Of the point to test)
		*/
		float CalculatePixelDepth(const std::array<glm::vec4, 3>& p_vertices, const glm::vec3& p_barycentricCoords) const;

		/**
		* Return true if the current culling mode is satisfied
		* @param p_triange
		*/
		bool IsCullingModeSatisfied(const Maths::Triangle2D& p_triangle);

		/**
		* Verify is Rasterizer is allow to rasterize
		*/
		bool CanRasterize() const;

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
		Buffers::DepthBuffer m_depthBuffer;
		Buffers::TextureBuffer m_rasterizationOutputBuffer;

		ERasterizationDrawMode m_rasterizationDrawMode;
		ERasterizationCullingMode m_rasterizationCullingMode;

		bool m_limitTriangleRasterization;
		uint64_t m_rasterizedTrianglesLimit;
		uint64_t m_rasterizedTriangles;
	};
}

#endif // _RASTERBOY_H
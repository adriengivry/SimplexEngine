/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESH_H
#define _MESH_H

#include "Rasterizer/Data/Vertex.h"

namespace Rasterizer::Data
{
	/**
	* The mesh class is a set of vertices
	*/
	class Mesh final
	{
	public:
		/**
		* Create an empty mesh
		*/
		Mesh();

		/**
		* Create a mesh filled with given vertices
		* @param p_vertices
		*/
		Mesh(std::vector<Vertex>& p_vertices);

		/**
		* Add a vertex to the mesh
		* @param p_vertex
		*/
		void AddVertex(const Vertex& p_vertex);

		/**
		* Return the vector of Vertex of the mesh
		*/
		const std::vector<Vertex>& GetVertices() const;

	private:
		std::vector<Vertex> m_vertices;
	};
}

#endif // _MESH_H
/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESH_H
#define _MESH_H

#include "Rasterizer/Data/Vertex.h"
#include "Rasterizer/Data/EPrimitive.h"

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
		* Create a mesh from a file
		* @param p_filename
		*/
		Mesh(const std::string& p_filename);

		/**
		* Create a mesh filled with given vertices
		* @param p_vertices
		*/
		Mesh(std::vector<Vertex>& p_vertices);

		/**
		* Create a mesh using a primitive
		* @param p_primitive
		*/
		Mesh(EPrimitive p_primitive);

		/**
		* Replace this mesh by the cube primitive
		*/
		void MakeCube();

		/**
		* Add a vertex to the mesh
		* @param p_vertex
		* @param p_autoIndex (Automatically add an indice to this vertex)
		*/
		void AddVertex(const Vertex& p_vertex, bool p_autoIndice = true);

		/**
		* Add an indice to the mesh
		* @param p_indice
		*/
		void AddIndice(uint32_t p_indice);

		/**
		* Return the vector of Vertex of the mesh
		*/
		const std::vector<Vertex>& GetVertices() const;

		/**
		* Return the vector of indices of the mesh
		*/
		const std::vector<uint32_t>& GetIndices() const;

	private:
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}

#endif // _MESH_H
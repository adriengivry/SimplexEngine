/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESH_H
#define _MESH_H

#include <vector>

#include "SimplexEngine/Data/Vertex.h"

namespace SimplexEngine::Resources
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
		Mesh() = default;

		/**
		* Create a mesh from a file
		* @param p_filename
		*/
		Mesh(const std::string& p_filename);

		/**
		* Add a vertex to the mesh
		* @param p_vertex
		* @param p_autoIndex (Automatically add an indice to this vertex)
		*/
		void AddVertex(const Data::Vertex& p_vertex, bool p_autoIndice = true);

		/**
		* Add an indice to the mesh
		* @param p_indice
		*/
		void AddIndice(uint32_t p_indice);

		/**
		* Clear any information contained in this mesh
		*/
		void ClearData();

		/**
		* Return the vector of Vertex of the mesh
		*/
		const std::vector<Data::Vertex>& GetVertices() const;

		/**
		* Return the vector of indices of the mesh
		*/
		const std::vector<uint32_t>& GetIndices() const;

	private:
		std::vector<Data::Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}

#endif // _MESH_H
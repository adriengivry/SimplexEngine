/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <vector>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Data/Vertex.h"

#pragma once
#ifndef _EASYASSIMP_H
#define _EASYASSIMP_H

namespace SimplexEngine::Utils
{
	/**
	* A simple class to load assimp model data (Vertices only)
	*/
	class API_SIMPLEXENGINE EasyAssimp final
	{
	public:
		/* Make the class static (No instanciation) */
		EasyAssimp() = default;

		/**
		* Simply load vertices from a file using assimp
		* Return true on success
		* @param p_filename
		* @param p_outBuffer
		*/
		static bool LoadVertices(const std::string& p_fileName, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices);

	private:
		static void ProcessNode(struct aiNode* p_node, const struct aiScene* p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices);
		static void ProcessMesh(struct aiMesh* p_mesh, const struct aiScene* p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices);
	};
}

#endif // _EASYASSIMP_H
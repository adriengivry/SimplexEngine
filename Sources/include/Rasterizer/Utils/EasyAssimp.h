/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Rasterizer/Data/Vertex.h"

#pragma once
#ifndef _EASYASSIMP_H
#define _EASYASSIMP_H

namespace Rasterizer::Utils
{
	/**
	* A simple class to load assimp model data (Vertices only)
	*/
	class EasyAssimp final
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
		static void ProcessNode(aiNode* p_node, const aiScene* p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices);
		static void ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices);
	};
}

#endif // _EASYASSIMP_H
/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include "SimplexEngine/Tools/EasyAssimp.h"

bool SimplexEngine::Tools::EasyAssimp::LoadVertices(const std::string & p_fileName, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
{
	p_outBuffer.clear();

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(p_fileName, aiProcess_Triangulate | aiProcess_OptimizeMeshes);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ASSIMP FAILED: " << import.GetErrorString() << std::endl;
		return false;
	}

	ProcessNode(scene->mRootNode, scene, p_outBuffer, p_indices);

	return true;
}

void SimplexEngine::Tools::EasyAssimp::ProcessNode(aiNode* p_node, const aiScene* p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < p_node->mNumMeshes; ++i)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		ProcessMesh(mesh, p_scene, p_outBuffer, p_indices);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < p_node->mNumChildren; ++i)
	{
		ProcessNode(p_node->mChildren[i], p_scene, p_outBuffer, p_indices);
	}
}

void SimplexEngine::Tools::EasyAssimp::ProcessMesh(aiMesh * p_mesh, const aiScene * p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
{
	for (unsigned int i = 0; i < p_mesh->mNumVertices; ++i)
	{
		auto vertex = p_mesh->mVertices[i];
		auto normal = p_mesh->mNormals[i];

		/*
		aiMatrix4x4 transformation;
		transformation.FromEulerAnglesXYZ(aiVector3D(90.0f, 0.0f, 0.0f));

		vertex = transformation * vertex;
		normal = transformation * normal;
		*/
		

		p_outBuffer.push_back
		(
			{
				vertex.x,
				vertex.z,
				-vertex.y,
				normal.x,
				normal.z,
				-normal.y
			}
		);
	}

	for (unsigned int i = 0; i < p_mesh->mNumFaces; i++)
	{
		const aiFace& face = p_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			p_indices.push_back(static_cast<uint32_t>(face.mIndices[j]));
	}
}

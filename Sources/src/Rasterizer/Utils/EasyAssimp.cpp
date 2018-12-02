#include "Rasterizer/Utils/EasyAssimp.h"

bool Rasterizer::Utils::EasyAssimp::LoadVertices(const std::string & p_fileName, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
{
	p_outBuffer.clear();

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(p_fileName, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ASSIMP FAILED: " << import.GetErrorString() << std::endl;
		return false;
	}

	ProcessNode(scene->mRootNode, scene, p_outBuffer, p_indices);

	return true;
}

void Rasterizer::Utils::EasyAssimp::ProcessNode(aiNode * p_node, const aiScene * p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
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

void Rasterizer::Utils::EasyAssimp::ProcessMesh(aiMesh * p_mesh, const aiScene * p_scene, std::vector<Data::Vertex>& p_outBuffer, std::vector<uint32_t>& p_indices)
{
	for (unsigned int i = 0; i < p_mesh->mNumVertices; ++i)
	{
		p_outBuffer.push_back
		(
			{ 
				p_mesh->mVertices[i].x,
				p_mesh->mVertices[i].y,
				p_mesh->mVertices[i].z,
				p_mesh->mNormals[i].x,
				p_mesh->mNormals[i].y,
				p_mesh->mNormals[i].z 
			}
		);
	}

	for (unsigned int i = 0; i < p_mesh->mNumFaces; i++)
	{
		const aiFace face = p_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			p_indices.push_back(static_cast<uint32_t>(face.mIndices[j]));
	}
}

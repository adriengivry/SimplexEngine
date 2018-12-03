/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Entities/Model.h"

Rasterizer::Entities::Model::Model(const Resources::Mesh & p_mesh, const glm::vec3 & p_position, const glm::quat & p_rotation)
	: AEntity(p_position, p_rotation)
{
	m_meshes.push_back(std::cref(p_mesh));
}

const Rasterizer::Resources::Mesh& Rasterizer::Entities::Model::GetPrimaryMesh() const
{
	/* The mesh 0 is always available (Look at constructor for more information) */
	return m_meshes[0].get();
}

const std::vector<std::reference_wrapper<const Rasterizer::Resources::Mesh>>& Rasterizer::Entities::Model::GetMeshes() const
{
	return m_meshes;
}

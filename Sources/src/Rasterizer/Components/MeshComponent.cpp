/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Components/MeshComponent.h"

void Rasterizer::Components::MeshComponent::SetMesh(const Resources::Mesh & p_mesh)
{
	m_mesh = &p_mesh;
}

Rasterizer::Resources::Mesh const* Rasterizer::Components::MeshComponent::GetMesh()
{
	return m_mesh;
}

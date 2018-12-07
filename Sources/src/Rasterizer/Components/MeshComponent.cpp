/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Components/MeshComponent.h"
#include "Rasterizer/Actors/Actor.h"

Rasterizer::Components::MeshComponent::MeshComponent(Actors::Actor& p_owner, Resources::Mesh& p_mesh) :
	AActorComponent(p_owner)
{
	SetMesh(p_mesh);
}

void Rasterizer::Components::MeshComponent::SetMesh(Resources::Mesh& p_mesh)
{
	m_mesh = &p_mesh;
}

Rasterizer::Resources::Mesh* Rasterizer::Components::MeshComponent::GetMesh() const
{
	return m_mesh;
}

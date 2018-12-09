/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/MeshComponent.h"
#include "SimplexEngine/Actors/Actor.h"
#include "SimplexEngine/Materials/AMaterial.h"

SimplexEngine::Components::MeshComponent::MeshComponent(Actors::Actor& p_owner, Resources::Mesh& p_mesh) :
	AActorComponent(p_owner)
{
	SetMesh(p_mesh);
}

void SimplexEngine::Components::MeshComponent::SetMesh(Resources::Mesh& p_mesh)
{
	m_mesh = &p_mesh;
}

SimplexEngine::Resources::Mesh* SimplexEngine::Components::MeshComponent::GetMesh() const
{
	return m_mesh;
}

SimplexEngine::Materials::AMaterial * SimplexEngine::Components::MeshComponent::GetMaterial() const
{
	return m_material.get();
}

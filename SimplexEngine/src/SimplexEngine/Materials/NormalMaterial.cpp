/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Materials/NormalMaterial.h"
#include "SimplexEngine/Actors/Actor.h"
#include "SimplexEngine/Components/MeshComponent.h"

void SimplexEngine::Materials::NormalMaterial::UpdateUniforms(const Components::CameraComponent & p_cameraComponent, const Components::MeshComponent & p_meshComponent)
{
	SetUniform("mvp", p_cameraComponent.GetViewProjectionMatrix() * p_meshComponent.owner->transform.GetWorldMatrix());
	SetUniform("modelMatrix", p_meshComponent.owner->transform.GetWorldMatrix());
}

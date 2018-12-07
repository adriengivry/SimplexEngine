/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Materials/LambertMaterial.h"
#include "Rasterizer/Actors/Actor.h"

void Rasterizer::Materials::LambertMaterial::UpdateUniforms(const Components::CameraComponent& p_cameraComponent, const Components::MeshComponent& p_meshComponent)
{
	SetUniform("mvp", p_cameraComponent.GetViewProjectionMatrix() * p_meshComponent.owner->transform.GetWorldMatrix());
	SetUniform("modelMatrix", p_meshComponent.owner->transform.GetWorldMatrix());
}
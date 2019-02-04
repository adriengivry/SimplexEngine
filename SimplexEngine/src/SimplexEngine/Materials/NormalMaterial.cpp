/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Materials/NormalMaterial.h"
#include "SimplexEngine/Actors/Actor.h"
#include "SimplexEngine/Components/MeshComponent.h"

void SimplexEngine::Materials::NormalMaterial::UpdateUniforms(const MaterialData& p_materialData)
{
	SetUniform("mvp", p_materialData.mainCamera.GetViewProjectionMatrix() * p_materialData.mesh.owner->transform.GetWorldMatrix());
	SetUniform("modelMatrix", p_materialData.mesh.owner->transform.GetWorldMatrix());
}

/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Materials/LambertMaterial.h"

void Rasterizer::Materials::LambertMaterial::UpdateUniforms(const Entities::Camera& p_camera, const Entities::Model & p_model)
{
	SetUniform("mvp", p_camera.GetViewProjectionMatrix() *p_model.transform.GetWorldMatrix());
	SetUniform("modelMatrix", p_model.transform.GetWorldMatrix());
}
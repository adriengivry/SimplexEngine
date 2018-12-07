/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Materials/AMaterial.h"

Rasterizer::Shaders::AShader & Rasterizer::Materials::AMaterial::GetShaderInstance()
{
	return *m_shaderInstance;
}

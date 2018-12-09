/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Materials/AMaterial.h"

SimplexEngine::Shaders::AShader & SimplexEngine::Materials::AMaterial::GetShaderInstance()
{
	return *m_shaderInstance;
}

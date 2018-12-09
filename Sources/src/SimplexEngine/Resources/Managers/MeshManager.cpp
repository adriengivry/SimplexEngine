/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Resources/Managers/MeshManager.h"

SimplexEngine::Resources::Mesh * SimplexEngine::Resources::Managers::MeshManager::Load(const std::string & p_path)
{
	return new Mesh(p_path);
}

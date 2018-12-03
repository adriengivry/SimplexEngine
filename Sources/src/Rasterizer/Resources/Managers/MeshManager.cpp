/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Resources/Managers/MeshManager.h"

Rasterizer::Resources::Mesh * Rasterizer::Resources::Managers::MeshManager::Load(const std::string & p_path)
{
	return new Mesh(p_path);
}

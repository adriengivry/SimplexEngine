/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Resources/Managers/AResourceManager.h"
#include "Rasterizer/Resources/Mesh.h"

#pragma once
#ifndef _MESHMANAGER_H
#define _MESHMANAGER_H

namespace Rasterizer::Resources::Managers
{
	/**
	* The mesh manager is a resource manager that can carry meshes
	*/
	class MeshManager final : public AResourceManager<Resources::Mesh>
	{
	public:
		MeshManager() : AResourceManager("config/resources/meshes.cfg") {}

	protected:
		virtual Resources::Mesh* Load(const std::string & p_path) override;
	};
}

#endif // _MESHMANAGER_H
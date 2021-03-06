/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESHMANAGER_H
#define _MESHMANAGER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Resources/Managers/AResourceManager.h"
#include "SimplexEngine/Resources/Mesh.h"

namespace SimplexEngine::Resources::Managers
{
	/**
	* The mesh manager is a resource manager that can carry meshes
	*/
	class API_SIMPLEXENGINE MeshManager final : public AResourceManager<Resources::Mesh>
	{
	public:
		/**
		* Constructor of the mesh manager
		* @param p_meshesIndexerPath
		*/
		MeshManager(const std::string& p_meshesIndexerPath);

	protected:
		/**
		* Indicates how to load a mesh
		* @param p_path
		*/
		virtual Resources::Mesh* Load(const std::string & p_path) override;
	};
}

#endif // _MESHMANAGER_H
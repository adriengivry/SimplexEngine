/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ACTOR_H
#define _ACTOR_H

#include "Rasterizer/Data/Mesh.h"
#include "Rasterizer/Entities/AEntity.h"

namespace Rasterizer::Entities
{
	/**
	* The Actor class is an entity (Localized in world space) with at least one mesh 
	*/
	class Actor final : public AEntity
	{
	public:
		/**
		* Create a model with a mesh and some transformations
		* @param p_mesh
		* @param p_position
		* @param p_rotation
		*/
		Actor(const Data::Mesh& p_mesh, const AltMath::Vector3f& p_position, const AltMath::Quaternion& p_rotation);

		/**
		* Return the default mesh
		*/
		const Data::Mesh& GetPrimaryMesh() const;

		/**
		* Return the vector of meshes
		*/
		const std::vector<std::reference_wrapper<const Data::Mesh>>& GetMeshes() const;

	private:
		std::vector<std::reference_wrapper<const Data::Mesh>> m_meshes;
	};
}

#endif // _ACTOR_H
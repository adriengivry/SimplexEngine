/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include "Rasterizer/Data/Mesh.h"
#include "Rasterizer/Entities/AEntity.h"

namespace Rasterizer::Entities
{
	/**
	* The Model class is an entity (Localized in world space) with at least one mesh 
	*/
	class Model final : public AEntity
	{
	public:
		/**
		* Create a model with a mesh and some transformations
		* @param p_mesh
		* @param p_position
		* @param p_rotation
		*/
		Model(const Data::Mesh& p_mesh, const AltMath::Vector3f& p_position, const AltMath::Quaternion& p_rotation);

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

#endif // _MODEL_H
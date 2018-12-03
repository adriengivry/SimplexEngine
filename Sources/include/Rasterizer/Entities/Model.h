/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include "Rasterizer/Resources/Mesh.h"
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
		Model(const Resources::Mesh& p_mesh, const glm::vec3& p_position, const glm::quat& p_rotation);

		/**
		* Return the default mesh
		*/
		const Resources::Mesh& GetPrimaryMesh() const;

		/**
		* Return the vector of meshes
		*/
		const std::vector<std::reference_wrapper<const Resources::Mesh>>& GetMeshes() const;

	private:
		std::vector<std::reference_wrapper<const Resources::Mesh>> m_meshes;
	};
}

#endif // _MODEL_H
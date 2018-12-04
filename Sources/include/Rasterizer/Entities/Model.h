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
		* @param p_localPosition
		* @param p_localRotation
		* @param p_localScale
		*/
		Model(const Resources::Mesh& p_mesh, const glm::vec3& p_localPosition = glm::vec3(0.0f, 0.0f, 0.0f), const glm::quat& p_localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& p_localScale = glm::vec3(1.0f, 1.0f, 1.0f));

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
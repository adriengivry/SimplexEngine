/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include "Rasterizer/Components/AActorComponent.h"
#include "Rasterizer/Resources/Mesh.h"

namespace Rasterizer::Components
{
	class MeshComponent : public AActorComponent
	{
	public:
		/**
		* Set a mesh for the mesh component
		* @param p_mesh
		*/
		void SetMesh(const Resources::Mesh& p_mesh);

		/**
		* Return the current mesh (Or nullptr if not set)
		*/
		Resources::Mesh const* GetMesh();

	private:
		Resources::Mesh const* m_mesh;
	};
}

#endif // _MESHCOMPONENT_H

/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include "SimplexEngine/Components/AActorComponent.h"
#include "SimplexEngine/Resources/Mesh.h"

namespace SimplexEngine::Components
{
	class MeshComponent : public AActorComponent
	{
	public:
		/**
		* Mesh component constructor
		* @param p_owner
		*/
		MeshComponent(Actors::Actor& p_owner, Resources::Mesh& p_mesh);

		/**
		* Needed
		*/
		virtual void Test() override {}

		/**
		* Set a mesh for the mesh component
		* @param p_mesh
		*/
		void SetMesh(Resources::Mesh& p_mesh);

		/**
		* Return the current mesh (Or nullptr if not set)
		*/
		Resources::Mesh* GetMesh() const;

	private:
		Resources::Mesh* m_mesh;
	};
}

#endif // _MESHCOMPONENT_H

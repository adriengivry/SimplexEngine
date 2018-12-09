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
#include "SimplexEngine/Materials/AMaterial.h"

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
		* Define the material to attach to this mesh
		* No arguments are needed, only the type of material
		* is requiered (Template parameter)
		*/
		template<typename T>
		void DefineMaterial() { m_material = std::make_unique<T>(); }

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

		/**
		* Return the current material (Or nullptr if not set)
		*/
		Materials::AMaterial* GetMaterial() const;

	private:
		Resources::Mesh* m_mesh;
		std::unique_ptr<Materials::AMaterial> m_material;
	};
}

#endif // _MESHCOMPONENT_H

/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MESHCREATOR_H
#define _MESHCREATOR_H

#include "SimplexEngine/Resources/Mesh.h"

namespace SimplexEngine::Tools
{
	/**
	* Static class that can create meshes from scratch (Primitives)
	*/
	class MeshCreator final
	{
	public:
		/* Static class */
		MeshCreator() = delete;

		/**
		* Make the given mesh a cube
		* @param p_outMesh (Any vertex in this mesh will get replaced by cube vertices)
		* @warning Normals aren't generated
		*/
		static void CreateCube(Resources::Mesh& p_outMesh);
	};
}

#endif // _MESHCREATOR_H
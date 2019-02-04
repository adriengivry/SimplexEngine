/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MATERIALDATA_H
#define _MATERIALDATA_H

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Components { class CameraComponent; }
namespace SimplexEngine::Components { class MeshComponent; }

namespace SimplexEngine::Materials
{
	/**
	* Contains informations that the material can manipulate and send to the shader
	*/
	struct API_SIMPLEXENGINE MaterialData final
	{
		/* The currently binded CameraComponent in the scene */
		const SimplexEngine::Components::CameraComponent& mainCamera;

		/* The MeshComponent used for this draw call */
		const SimplexEngine::Components::MeshComponent&	mesh;

		/* The elapsed time since the engine starts (Seconds) */
		float totalTime;

		/* The elapsed time between the current frame and the last one (Seconds) */
		float deltaTime;
	};
}

#endif // _MATERIALDATA_H

/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SCENEPARSER_H
#define _SCENEPARSER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Components/MeshComponent.h"
#include "SimplexEngine/Scenes/AScene.h"

namespace SimplexEngine::Tools
{
	/**
	* A tool to collect data from scene
	*/
	class API_SIMPLEXENGINE SceneParser final
	{
	public:
		/* Static class */
		SceneParser() = delete;

		/**
		* Return the main camera of the given scene (First found)
		* @param p_scene
		*/
		static Components::CameraComponent const* GetMainCamera(const Scenes::AScene& p_scene);

		/**
		* Find every cameras component in the given scene
		* @param p_scene
		*/
		static std::vector<std::reference_wrapper<const Components::CameraComponent>> FindCameras(const Scenes::AScene& p_scene);

		/**
		* Find every meshes component in the given scene
		* @param p_scene
		*/
		static std::vector<std::reference_wrapper<const Components::MeshComponent>> FindMeshes(const Scenes::AScene& p_scene);
	};
}

#endif // _SCENEPARSER_H
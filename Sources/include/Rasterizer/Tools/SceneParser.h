/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SCENEPARSER_H
#define _SCENEPARSER_H

#include "Rasterizer/Components/CameraComponent.h"
#include "Rasterizer/Components/MeshComponent.h"
#include "Rasterizer/Scenes/AScene.h"

namespace Rasterizer::Tools
{
	/**
	* A tool to collect data from scene
	*/
	class SceneParser final
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
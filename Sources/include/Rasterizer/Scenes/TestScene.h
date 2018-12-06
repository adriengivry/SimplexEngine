/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TESTSCENE_H
#define _TESTSCENE_H

#include "Rasterizer/Scenes/AScene.h"

namespace Rasterizer::Scenes
{
	/**
	* A scene for test purpose
	*/
	class TestScene final : public AScene
	{
	public:
		/**
		* TestScene constructor
		*/
		TestScene(SCENE_PARAMETERS);

	private:
		virtual void CreateCameras() override;
		virtual void CreateModels() override;
		virtual void CreateScripts() override;
		virtual void DefineParents() override;
	};
}

#endif // _TESTSCENE_H
/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/


#include <SimplexEngine/SimplexEngine.h>

#include <random>

#pragma once
#ifndef _PHYSICSSCENE_H
#define _PHYSICSSCENE_H

namespace Example::Scenes
{
	class PhysicsScene final : public SimplexEngine::Scenes::AScene
	{
	public:
		PhysicsScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST{}

		virtual void OnLoad() override;
		virtual void OnUnload() override;
		virtual void Update(float p_deltaTime) override;

	private:
		std::default_random_engine m_randEngine;
		std::uniform_int_distribution<int> m_colorRange{ 0, 255 };
	};
}

#endif // _PHYSICSSCENE_H
/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ROTATEOVERTIME_H
#define _ROTATEOVERTIME_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/SceneScripts/ISceneScript.h"
#include "SimplexEngine/Actors/Actor.h"

namespace SimplexEngine::Scripts::SceneScripts
{
	/**
	* Rotate an entity over time
	*/
	class API_SIMPLEXENGINE RotateOverTime final : public ISceneScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_target
		* @param p_rotationSpeed
		* @param p_rotationAxis
		*/
		RotateOverTime(Actors::Actor& p_target, float p_rotationSpeed, const glm::vec3& p_rotationAxis = {0.0f, 1.0f, 0.0f});

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Actors::Actor& m_target;
		float m_rotationSpeed;
		glm::vec3 m_rotationAxis;
	};
}

#endif // _ROTATEOVERTIME_H
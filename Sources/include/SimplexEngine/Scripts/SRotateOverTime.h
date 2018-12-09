/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/IScript.h"
#include "SimplexEngine/Actors/Actor.h"

#pragma once
#ifndef _SROTATEOVERTIME_H
#define _SROTATEOVERTIME_H

namespace SimplexEngine::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SRotateOverTime final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_target
		* @param p_rotationSpeed
		*/
		SRotateOverTime(Actors::Actor& p_target, float p_rotationSpeed);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Actors::Actor& m_target;
		float m_rotationSpeed;
	};
}

#endif // _SROTATEOVERTIME_H
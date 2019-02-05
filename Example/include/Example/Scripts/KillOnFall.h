/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _KILLONFALL_H
#define _KILLONFALL_H

#include <SimplexEngine/SimplexEngine.h>

namespace Example::Scripts
{
	class KillOnFall : public SimplexEngine::Scripts::Behaviours::ABehaviour
	{
	public:
		KillOnFall(SimplexEngine::Actors::Actor& p_owner, float p_killHeight);

	private:
		virtual void Update(float p_deltaTime) override;

	private:
		float m_killHeight;
	};
}

#endif // _KILLONFALL_H

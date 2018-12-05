/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _WINDOWSTATE_H
#define _WINDOWSTATE_H

namespace Rasterizer::Core
{
	enum class EWindowState
	{
		NONE,
		OK,
		INIT_FAILED,
	};
}

#endif // _WINDOWSTATE_H
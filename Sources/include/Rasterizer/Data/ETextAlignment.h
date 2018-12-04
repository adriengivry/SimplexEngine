/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ETEXTALIGNMENT_H
#define _ETEXTALIGNMENT_H

namespace Rasterizer::Data
{
	enum class ETextHorizontalAlignment
	{
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	enum class ETextVerticalAlignment
	{
		ALIGN_TOP,
		ALIGN_BOTTOM,
		ALIGN_CENTER
	};
}

#endif // _ETEXTALIGNMENT_H
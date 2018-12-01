/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _GENERICS_H
#define _GENERICS_H

#include "AltMath/export.h"

namespace AltMath
{
	namespace Tools
	{
		/**
		 * This class exposes some constant variables to the user
		 */
		struct ALTMATH_API Generics final
		{
			static const float	Pi;
			static const float	E;

			/* Desactivate the constructor (Un-instanciable static class) */
			Generics() = delete;
		};
	}
}

#endif //_GENERICS_H
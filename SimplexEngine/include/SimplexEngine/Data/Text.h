/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ETEXT_H
#define _ETEXT_H

#include <string>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Data/ETextAlignment.h"
#include "SimplexEngine/Data/EFontSize.h"

namespace SimplexEngine::Data
{
	/**
	* A simple data container used to render text on screen
	*/
	struct API_SIMPLEXENGINE Text final
	{
		std::string content;
		std::pair<int16_t, int16_t> position;
		Data::EFontSize fontSize;
		Data::Color color = Data::Color::White;
		Data::ETextHorizontalAlignment horizontalAlign = Data::ETextHorizontalAlignment::ALIGN_LEFT;
		Data::ETextVerticalAlignment verticalAlign = Data::ETextVerticalAlignment::ALIGN_TOP;
	};
}

#endif // _ETEXTALIGNMENT_H
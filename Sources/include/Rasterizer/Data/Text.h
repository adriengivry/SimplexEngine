/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ETEXT_H
#define _ETEXT_H

#include <string>

#include "Rasterizer/Data/ETextAlignment.h"
#include "Rasterizer/Data/EFontSize.h"

namespace Rasterizer::Data
{
	/**
	* A simple data container used to render text on screen
	*/
	struct Text
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
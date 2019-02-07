/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Data/Color.h"

const SimplexEngine::Data::Color SimplexEngine::Data::Color::Red = Color{ 255, 0, 0 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Green = Color{ 0, 255, 0 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Blue = Color{ 0, 0, 255 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::White = Color{ 255, 255, 255 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Black = Color{ 0, 0, 0 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Yellow = Color{ 255, 255, 0 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Cyan = Color{ 0, 255, 255 };
const SimplexEngine::Data::Color SimplexEngine::Data::Color::Magenta = Color{ 255, 0, 255 };

SimplexEngine::Data::Color::Color(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a) : r(p_r), g(p_g), b(p_b), a(p_a) {}

SimplexEngine::Data::Color::Color(const glm::vec4 & p_normalizedColor) :
	Color
	(
		static_cast<uint8_t>(p_normalizedColor.x * 255.0f),
		static_cast<uint8_t>(p_normalizedColor.y * 255.0f),
		static_cast<uint8_t>(p_normalizedColor.z * 255.0f),
		static_cast<uint8_t>(p_normalizedColor.w * 255.0f)
	)
{
}

SimplexEngine::Data::Color::Color(const glm::vec3 & p_normalizedColor) :
	Color
	(
		static_cast<uint8_t>(p_normalizedColor.x * 255.0f),
		static_cast<uint8_t>(p_normalizedColor.y * 255.0f),
		static_cast<uint8_t>(p_normalizedColor.z * 255.0f)
	)
{
}

SimplexEngine::Data::Color::Color(uint32_t p_packedData) :
	a(p_packedData),
	b(p_packedData >> 8),
	g(p_packedData >> 16),
	r(p_packedData >> 24)
{
}

std::tuple<float, float, float, float> SimplexEngine::Data::Color::GetNormalized() const
{
	return std::make_tuple(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

glm::vec4 SimplexEngine::Data::Color::GetNormalizedVec4() const
{
	return glm::vec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

glm::vec3 SimplexEngine::Data::Color::GetNormalizedVec3() const
{
	return glm::vec3(r / 255.f, g / 255.f, b / 255.f);
}

uint32_t SimplexEngine::Data::Color::Pack() const
{
	return (r << 24) | (g << 16) | (b << 8) | a;
}

SimplexEngine::Data::Color SimplexEngine::Data::Color::Mix(const Color & p_color1, const Color & p_color2, float p_alpha)
{
	return Data::Color(glm::mix(p_color1.GetNormalizedVec3(), p_color2.GetNormalizedVec3(), p_alpha));
}

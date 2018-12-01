#ifndef ALTMATH_EXPORT_INCLUDE
#pragma once

#ifdef ALTMATH_EXPORT
#define ALTMATH_API __declspec(dllexport)
#else
#define ALTMATH_API __declspec(dllimport)
#endif

#endif // !ALTMATH_EXPORT_INCLUDE

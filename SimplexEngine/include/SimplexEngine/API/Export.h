/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EXPORT_H
#define _EXPORT_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef SIMPLEXENGINE_EXPORT
#define API_SIMPLEXENGINE __declspec(dllexport)
#else
#define API_SIMPLEXENGINE __declspec(dllimport)
#endif // GYVRINI_EXPORT

#endif // _EXPORT_H
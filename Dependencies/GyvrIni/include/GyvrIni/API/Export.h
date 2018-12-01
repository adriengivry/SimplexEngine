/**
* Project GyvrIni
* @author Adrien Givry
* @version 1.0
*/

#ifndef _GYVRINI_EXPORT_H
#define _GYVRINI_EXPORT_H
#pragma once

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef GYVRINI_EXPORT
#define API_GYVRINI __declspec(dllexport)
#else
#define API_GYVRINI __declspec(dllimport)
#endif // GYVRINI_EXPORT

#endif // _GYVRINI_EXPORT_H
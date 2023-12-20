/**
* Project GyvrIni
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _GYVRINI_INIFILE_INL
#define _GYVRINI_INIFILE_INL

#include "IniFile.h"
#include <assert.h>

template<GyvrIni::Core::IniType T>
inline T GyvrIni::Core::IniFile::Get(const std::string& p_key)
{
	if constexpr (std::is_same<bool, T>::value)
	{
		if (!IsKeyExisting(p_key))
			return false;

		return StringToBoolean(m_data[p_key]);
	}
	else if constexpr (std::is_same<std::string, T>::value)
	{
		if (!IsKeyExisting(p_key))
			return std::string("NULL");

		return m_data[p_key];
	}
	else if constexpr (std::is_integral<T>::value)
	{
		if (!IsKeyExisting(p_key))
			return static_cast<T>(0);

		return static_cast<T>(std::atoi(m_data[p_key].c_str()));
	}
	else if constexpr (std::is_floating_point<T>::value)
	{
		if (!IsKeyExisting(p_key))
			return static_cast<T>(0.0f);

		return static_cast<T>(std::atof(m_data[p_key].c_str()));
	}
}

template<GyvrIni::Core::IniType T>
inline bool GyvrIni::Core::IniFile::Set(const std::string& p_key, const T& p_value)
{
	if (IsKeyExisting(p_key))
	{
		if constexpr (std::is_same<bool, T>::value)
		{
			m_data[p_key] = p_value ? "true" : "false";
		}
		else if constexpr (std::is_same<std::string, T>::value)
		{
			m_data[p_key] = p_value;
		}
		else if constexpr (std::is_integral<T>::value)
		{
			m_data[p_key] = std::to_string(p_value);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			m_data[p_key] = std::to_string(p_value);
		}

		return true;
	}

	return false;
}

template<GyvrIni::Core::IniType T>
inline bool GyvrIni::Core::IniFile::Add(const std::string & p_key, const T & p_value)
{
	if (!IsKeyExisting(p_key))
	{
		if constexpr (std::is_same<bool, T>::value)
		{
			RegisterPair(p_key, p_value ? "true" : "false");
		}
		else if constexpr (std::is_same<std::string, T>::value)
		{
			RegisterPair(p_key, p_value);
		}
		else if constexpr (std::is_integral<T>::value)
		{
			RegisterPair(p_key, std::to_string(p_value));
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			RegisterPair(p_key, std::to_string(p_value));
		}

		return true;
	}

	return false;
}

#endif // _GYVRINI_INIFILE_INL
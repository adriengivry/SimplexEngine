/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ARESOURCEMANAGER_INL
#define _ARESOURCEMANAGER_INL

#include "SimplexEngine/Resources/Managers/AResourceManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace SimplexEngine::Resources::Managers
{
	template<typename T>
	inline AResourceManager<T>::AResourceManager(const std::string & p_pathsFile)
	{
		m_pathsFile = p_pathsFile;
		LoadPaths(m_pathsFile);
	}

	template<typename T>
	inline AResourceManager<T>::~AResourceManager()
	{
		PurgeResources();
	}

	template<typename T>
	inline std::unordered_map<std::string, std::pair<T*, unsigned int>>& AResourceManager<T>::GetEveryResources()
	{
		return m_resources;
	}

	template<typename T>
	inline T * AResourceManager<T>::RequireAndGet(const std::string & p_id)
	{
		T* result = GetResource(p_id);

		if (!result)
		{
			if (RequireResource(p_id))
				return GetResource(p_id);

			return nullptr;
		}

		return result;
	}

	template<typename T>
	inline T * AResourceManager<T>::GetResource(const std::string & p_id)
	{
		auto res = Find(p_id);
		return (res ? res->first : nullptr);
	}

	template<typename T>
	inline std::string AResourceManager<T>::GetPath(const std::string & p_id)
	{
		const auto path = m_paths.find(p_id);
		return (path != m_paths.end() ? path->second : "");
	}

	template<typename T>
	inline bool AResourceManager<T>::RequireResource(const std::string & p_id)
	{
		auto res = Find(p_id);
		if (res)
		{
			++res->second;
			return true;
		}
		const auto path = m_paths.find(p_id);
		if (path == m_paths.end()) { return false; }
		T* resource = Load(path->second);
		if (!resource) { return false; }
		m_resources.emplace(p_id, std::make_pair(resource, 1));
		return true;
	}

	template<typename T>
	inline bool AResourceManager<T>::ReleaseResource(const std::string & p_id)
	{
		auto res = Find(p_id);

		if (!res)
			return false;

		--res->second;

		if (!res->second)
			Unload(p_id);

		return true;
	}

	template<typename T>
	inline void AResourceManager<T>::PurgeResources()
	{
		while (m_resources.begin() != m_resources.end())
		{
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
	}

	template<typename T>
	inline std::pair<T*, unsigned int>* AResourceManager<T>::Find(const std::string & p_id)
	{
		auto itr = m_resources.find(p_id);
		return (itr != m_resources.end() ? &itr->second : nullptr);
	}

	template<typename T>
	inline bool AResourceManager<T>::Unload(const std::string & p_id)
	{
		auto itr = m_resources.find(p_id);
		if (itr == m_resources.end()) { return false; }
		delete itr->second.first;
		m_resources.erase(itr);
		return true;
	}

	template<typename T>
	inline void AResourceManager<T>::LoadPaths(const std::string & l_pathFile)
	{
		std::ifstream paths;
		paths.open(l_pathFile);
		if (paths.is_open())
		{
			std::string line;
			while (std::getline(paths, line))
			{
				std::stringstream keystream(line);
				std::string pathName;
				std::string path;
				keystream >> pathName;
				keystream >> path;
				m_paths.emplace(pathName, path);
			}
			paths.close();
			return;
		}

		std::cout << "Failed loading the path file: " << l_pathFile << std::endl;
	}
}

#endif // _ARESOURCEMANAGER_INL

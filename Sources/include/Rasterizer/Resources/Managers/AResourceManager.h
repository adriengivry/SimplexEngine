/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ARESOURCEMANAGER_H
#define _ARESOURCEMANAGER_H

#include <unordered_map>
#include <string>

namespace Rasterizer::Resources::Managers
{
	/**
	* Base class for any ResourceManager
	*/
	template <typename T>
	class AResourceManager
	{
	public:
		/**
		* The constructor for the AResourceManager
		* @param p_pathsFile
		*/
		explicit AResourceManager(const std::string& p_pathsFile);

		/**
		* Destructor for the AResourceManager that take care about freeing resources
		*/
		virtual ~AResourceManager();

		/**
		* Return an unordered map of every loaded resources
		*/
		std::unordered_map<std::string, std::pair<T*, unsigned int>>& GetEveryResources();

		/**
		* Load the resource associated to the given ID to the memory (If not already done) and return the loaded resource
		* @param p_id
		*/
		T* RequireAndGet(const std::string& p_id);

		/**
		* Return the resource associated to the given ID
		* @param p_id
		*/

		T* GetResource(const std::string& p_id);

		/**
		* Return the path associated to the given resource ID
		* @param p_id
		*/
		std::string GetPath(const std::string& p_id);

		/**
		* Load the resource associated to the given ID to the memory
		* @param p_id
		*/
		bool RequireResource(const std::string& p_id);

		/**
		* Free the resource associated to the given ID from the memory
		* @param p_id
		*/
		bool ReleaseResource(const std::string& p_id);

		/**
		* Free any resources loaded into the memory
		*/
		void PurgeResources();

	protected:
		virtual T* Load(const std::string& l_path) = 0;

	private:
		std::pair<T*, unsigned int>* Find(const std::string& l_id);
		bool Unload(const std::string& l_id);
		void LoadPaths(const std::string& l_pathFile);
		
	private:
		std::string m_pathsFile;
		std::unordered_map<std::string, std::pair<T*, unsigned int>>	m_resources;
		std::unordered_map<std::string, std::string>					m_paths;
	};
}

#include "AResourceManager.inl"

#endif // _ARESOURCEMANAGER_H
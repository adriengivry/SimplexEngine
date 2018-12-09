/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EVENT_H
#define _EVENT_H

#include <functional>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Eventing
{
	/**
	* A simple event that contains a vector of function callbacks. These functions will be called on invoke
	*/
	template<class... ArgTypes>
	class API_SIMPLEXENGINE Event final
	{
	public:
		/**
		* Simple shortcut for a generic function without return value
		*/
		typedef std::function<void(ArgTypes...)> Callback;

		/**
		* Unordered map of [callbackID, callback]
		*/
		typedef std::unordered_map<uint64_t, Callback> CallbackMap;

		/**
		* The ID of a listener (Registered callback).
		* This value is needed to remove a listener from an event
		*/
		typedef uint64_t ListenerID;

		/**
		* Add a function callback to this event
		* @param p_call
		*/
		ListenerID AddListener(Callback p_callback)
		{
			uint64_t listenerID = m_currentHashCode;
			m_callbacks.emplace(m_currentHashCode++, p_callback);
			return listenerID;
		}

		/**
		* Remove a function callback to this event using a Listener (Created when calling AddListener)
		* @param p_listener
		*/
		bool RemoveListener(const ListenerID& p_listenerID)
		{
			return m_callbacks.erase(p_listenerID) != 0;
		}

		/**
		* Remove every listeners to this event
		*/
		void RemoveAllListeners()
		{
			m_callbacks.clear();
		}

		/**
		* Return the number of callback registered
		*/
		uint64_t GetListenerCount()
		{
			return m_callbacks.size();
		}

		/**
		* Call every callbacks attached to this event
		* @param p_args (Variadic)
		*/
		void Invoke(ArgTypes... p_args)
		{
			for (auto const&[key, val] : m_callbacks)

				val(p_args...);
		}

	private:
		CallbackMap		m_callbacks;
		uint64_t		m_currentHashCode = 0;
	};
}

#endif // _EVENT_H
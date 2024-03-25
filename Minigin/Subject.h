#ifndef DAE_SUBJECT
#define DAE_SUBJECT

#include "Observer.h"
#include <vector>
#include <tuple>

namespace dae
{
	template <class... Arguments>
	class Observer;

	template <class... Arguments>
	class Subject final
	{
	public:
		Subject() = default;

		void AddObserver(Observer<Arguments...>* observer)
		{
			if (observer)
			{
				m_Observers.emplace_back(observer);
			}
		}

		void RemoveObserver(Observer<Arguments...>* observer)
		{
			auto removedObserverIt{ std::remove(m_Observers.begin(), m_Observers.end(), observer) };

			if (removedObserverIt != m_Observers.end())
			{
				m_Observers.erase(removedObserverIt);
			}
		}

		void NotifyObservers(std::tuple<Arguments...>arguments)
		{
			for (auto& observer : m_Observers)
			{
				observer->Notify(arguments);
			}
		}

	private:
		std::vector< Observer<Arguments...>* > m_Observers{};
	};
}

#endif
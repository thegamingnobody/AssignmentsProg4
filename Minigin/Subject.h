#ifndef DAE_SUBJECT
#define DAE_SUBJECT

#include "Observer.h"
#include <iostream>
#include <vector>
#include "Event.h"

namespace dae
{
	class Subject final
	{
	public:
		Subject() = default;

		void AddObserver(Observer* observer, EventType& eventType)
		{
			if (observer)
			{
				m_Observers.emplace_back(std::make_pair(eventType, observer));
			}
		}

		void RemoveObserver(Observer* observer)
		{
			auto removedObserverIt{ std::remove_if(m_Observers.begin(), m_Observers.end(), [observer](const std::pair<const EventType, Observer*>& pair)
				{
					return pair.second == observer;
				})};

			if (removedObserverIt != m_Observers.end())
			{
				m_Observers.erase(removedObserverIt);
			}
		}

		void NotifyObservers(const Event& event)
		{
			if (not IsTuple(event.m_args)) { return; }

			for (auto& observer : m_Observers)
			{
				if (event.m_type == observer.first)
				{
					observer.second->Notify(event.m_args);
				}
			}
		}

	private:
		bool IsTuple(std::any arguments)
		{
			std::string argumentType{ arguments.type().name() };
			std::string tupleName{ "class std::tuple" };

			for (int i = 0; i < tupleName.length(); ++i)
			{
				if (argumentType[i] != tupleName[i])
				{
					std::cout << "Argument is not a tuple\n";
					return false;
				}
			}

			return true;
		}

		std::vector< std::pair<EventType, Observer*> > m_Observers{};
	};
}

#endif
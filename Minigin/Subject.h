#ifndef DAE_SUBJECT
#define DAE_SUBJECT

#include "Observer.h"
#include <iostream>
#include <vector>

namespace dae
{
	class Subject final
	{
	public:
		Subject() = default;

		void AddObserver(Observer* observer)
		{
			if (observer)
			{
				m_Observers.emplace_back(observer);
			}
		}

		void RemoveObserver(Observer* observer)
		{
			auto removedObserverIt{ std::remove(m_Observers.begin(), m_Observers.end(), observer) };

			if (removedObserverIt != m_Observers.end())
			{
				m_Observers.erase(removedObserverIt);
			}
		}

		void NotifyObservers(std::any arguments)
		{
			if (not IsTuple(arguments)) { return; }

			for (auto& observer : m_Observers)
			{
				observer->Notify(arguments);
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

		std::vector< Observer* > m_Observers{};
	};
}

#endif
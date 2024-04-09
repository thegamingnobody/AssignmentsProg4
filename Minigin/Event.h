#ifndef DAE_EVENT
#define DAE_EVENT

#include <any>
#include <Tuple>
#include <iostream>

namespace dae
{
	enum class EventType
	{
		UpdateCounter,
		
	};

	struct Event
	{
		template<class... EventArguments>
		Event(const EventType& eventType, std::tuple<EventArguments...> arguments)
			: m_type(eventType)
			, m_numArgs(0)
			, m_args(arguments)
		{
			m_numArgs = sizeof...(EventArguments);
		}

		template<class... EventArguments>
		std::tuple<EventArguments...> GetArgumentsAsTuple() const
		{
			try
			{
				return std::any_cast<std::tuple<EventArguments...>>(m_args);
			}
			catch (const std::bad_any_cast& e)
			{
				std::cout << "Invalid Event Arguments!\n";
				throw e;
			}
		}
		//static const uint8_t MAX_ARGS = 8;

		EventType m_type;
		uint8_t m_numArgs;
		std::any m_args;
	};
}

#endif
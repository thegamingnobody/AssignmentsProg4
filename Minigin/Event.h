#ifndef DAE_EVENT
#define DAE_EVENT

namespace dae
{
	enum class EventType
	{
		PlayerDied
	};

	template<class... EventArguments>
	struct Event
	{
		Event(const EventType& eventType, std::tuple<EventArguments...> arguments)
			: m_type(eventType)
			, m_numArgs(0)
			, m_args(arguments)
		{
			m_numArgs = sizeof...(EventArguments);
		}

		static const uint8_t MAX_ARGS = 8;

		EventType m_type;
		uint8_t m_numArgs;
		std::tuple<EventArguments...> m_args;
	};
}

#endif
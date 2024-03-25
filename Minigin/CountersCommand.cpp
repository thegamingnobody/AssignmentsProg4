#include "CountersCommand.h"
#include "Event.h"
#include <string>

dae::CountersCommand::CountersCommand(dae::GameObject* actor, const std::string& targetCounterName, int const addedValue)
	: m_Actor(actor)
	, m_TargetCounterName(targetCounterName)
	, m_AddedValue(addedValue)
{
}

void dae::CountersCommand::Execute()
{
	Event<const std::string&, int const> eventToNotify{ dae::EventType::PlayerDied, std::tuple<const std::string&, int const>(m_TargetCounterName, m_AddedValue) };
	m_Actor->Notify(eventToNotify);
}
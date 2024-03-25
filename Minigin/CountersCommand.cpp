#include "CountersCommand.h"
#include <tuple>
#include "Event.h"

dae::CountersCommand::CountersCommand(dae::GameObject* actor, const std::string& targetCounterName, int const addedValue)
	: m_Actor(actor)
	, m_TargetCounterName(targetCounterName)
	, m_AddedValue(addedValue)
{
}

void dae::CountersCommand::Execute()
{
	Event<std::string, int> eventToNotify{ dae::EventType::PlayerDied, std::tuple<std::string, int>(m_TargetCounterName, m_AddedValue) };
	m_Actor->Notify(eventToNotify);
}
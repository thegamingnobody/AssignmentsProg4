#include "CountersCommand.h"

dae::CountersCommand::CountersCommand(dae::GameObject* actor, const std::string& targetCounterName, int const addedValue)
	: m_Actor(actor)
	, m_TargetCounterName(targetCounterName)
	, m_AddedValue(addedValue)
{
	m_CountersComponent = actor->GetComponent<dae::CounterComponent>();
	assert(m_CountersComponent.has_value());
}

void dae::CountersCommand::Execute()
{
	m_CountersComponent.value()->AddValue(m_TargetCounterName, m_AddedValue);
}

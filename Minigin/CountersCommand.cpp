#include "CountersCommand.h"
#include "Event.h"
#include <string>
#include "EventManager.h"
#include <ServiceLocator.h>
#include <chrono>

dae::CountersCommand::CountersCommand(int const playerNumber, const std::string& targetCounterName, int const addedValue)
	: m_TargetCounterName(targetCounterName)
	, m_AddedValue(addedValue)
{
	m_PlayerNumber = playerNumber;
}

void dae::CountersCommand::Execute()
{
	std::tuple<const std::string&, int const> eventArguments{ m_TargetCounterName, m_AddedValue };
	Event eventToNotify{ dae::EventType::UpdateCounter, eventArguments, m_PlayerNumber };

	dae::EventManager::GetInstance().PushEvent(eventToNotify);

	//auto start = std::chrono::high_resolution_clock::now();
	dae::ServiceLocator::GetSoundSystem().PlaySound(1, 0.1f);
	//auto end = std::chrono::high_resolution_clock::now();
	//auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//std::cout << "play took: " << elapsed << "ms\n";
}
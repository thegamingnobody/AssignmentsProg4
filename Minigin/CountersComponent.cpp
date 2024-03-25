#include "CountersComponent.h"
#include "GameObject.h"

void dae::CounterComponent::Update(float const)
{
}

void dae::CounterComponent::AddCounter(const std::string& counterName, int const maxValue, bool const capAtMaxValue)
{
	Counter temp{};
	temp.m_CurrentValue = maxValue;
	temp.m_MaxValue = maxValue;
	temp.m_CapAtMax = capAtMaxValue;

	m_Counters.insert({ counterName, temp });
	
}

void dae::CounterComponent::AddValue(const std::string& counterName, int const valueToAdd)
{
	auto counter{ m_Counters.find(counterName) };

	if (counter != m_Counters.end())
	{
		counter->second.m_CurrentValue += valueToAdd;
		if (counter->second.m_CapAtMax and counter->second.m_CurrentValue > counter->second.m_MaxValue)
		{
			counter->second.m_CurrentValue = counter->second.m_MaxValue;
		}
	}
}

void dae::CounterComponent::DecreaseValue(const std::string& counterName, int const valueToDecrease)
{
	AddValue(counterName, -valueToDecrease);
}

int dae::CounterComponent::GetCurrentValue(const std::string& counterName)
{
	auto counter{ m_Counters.find(counterName) };

	if (counter != m_Counters.end())
	{
		return counter->second.m_CurrentValue;
	}

	throw std::exception("Counter not found");
}

int dae::CounterComponent::GetMaxValue(const std::string& counterName)
{
	auto counter{ m_Counters.find(counterName) };

	if (counter != m_Counters.end())
	{
		return counter->second.m_MaxValue;
	}

	throw std::exception("Counter not found");

}

dae::CounterComponent::CounterComponent(dae::GameObject* object)
	: Component(object)
	, m_Counters()
{
	object->AddObserver(this);
}

void dae::CounterComponent::Notify(std::tuple<const std::string&, int const> eventArgs)
{
	AddValue(std::get<0>(eventArgs), std::get<1>(eventArgs));
}

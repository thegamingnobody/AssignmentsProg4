#ifndef COUNTERCOMPONENT
#define COUNTERCOMPONENT

#include "Component.h"
#include <string>
#include <map>
#include "Observer.h"
#include <tuple>

namespace dae 
{
	class CounterComponent : public Component, public Observer<const std::string&, int const>
	{
	public:
		void Update(float const elapsedTime) override;

		void AddCounter(const std::string& counterName, int const maxValue = 10, bool const capAtMaxValue = true);

		void AddValue(const std::string& counterName, int const valueToAdd);
		void DecreaseValue(const std::string& counterName, int const valueToDecrease);

		int GetCurrentValue(const std::string& counterName);
		int GetMaxValue(const std::string& counterName);

		CounterComponent(dae::GameObject* object);

		void Notify(std::tuple<const std::string&, int const> eventArgs) override;

	private:
		struct Counter
		{
			int m_CurrentValue;
			int m_MaxValue;
			bool m_CapAtMax;
		};
		std::map<std::string, Counter> m_Counters;
	};
}


#endif
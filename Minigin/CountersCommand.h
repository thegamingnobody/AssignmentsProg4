#ifndef COUNTERSCOMMAND
#define COUNTERSCOMMAND

#include "Command.h"
#include "CountersComponent.h"

namespace dae
{
	class CountersCommand final : public Command
	{
	public:
		CountersCommand(dae::GameObject* actor, const std::string& targetCounterName, int const addedValue);

		void Execute() override;

	private:
		dae::GameObject* m_Actor;
		std::string m_TargetCounterName;
		int m_AddedValue;
	};
}

#endif
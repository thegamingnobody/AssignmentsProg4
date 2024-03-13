#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"

namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(dae::GameObject* actor);

		void Execute() override;

	private:
		dae::GameObject* m_Actor;
	};
}
#endif
#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"

namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(dae::GameObject* actor, glm::vec3 direction);

		void Execute() override;

	private:
		dae::GameObject* m_Actor;
		const glm::vec3 m_Direction;
	};
}
#endif
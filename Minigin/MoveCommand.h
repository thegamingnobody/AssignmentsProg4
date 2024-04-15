#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"

namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(int const playerNumber, glm::vec3 direction);

		void Execute() override;

	private:
		const glm::vec3 m_Direction;
	};
}
#endif
#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"

class MoveCommand final : public Command 
{
	void Execute(dae::GameObject& actor) override;
};

#endif
#ifndef MOVECOMMAND
#define MOVECOMMAND

#include "Command.h"

class MoveCommand final : public Command 
{
public:
	void Execute(dae::GameObject& actor) override;
};

#endif
#ifndef COMMAND
#define COMMAND

#include "GameObject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(dae::GameObject& actor) = 0;
};

#endif
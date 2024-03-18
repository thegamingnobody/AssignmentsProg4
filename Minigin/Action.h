#ifndef ACTION
#define ACTION

#include <memory>
#include "Command.h"
#include "ButtonEnums.h"
#include <SDL_scancode.h>

namespace dae
{
	class Action
	{
	public:
		enum class DeviceType 
		{
			Controller,
			Keyboard
		};

		Action(const ControllerButtons& controllerButton, std::shared_ptr<Command> command, int const playerNumber);
		Action(const KeyboardKeys& keyboardKey, std::shared_ptr<Command> command, int const playerNumber);

		void Execute();

		int GetButton()				const;
		int GetPlayerNumber()		const { return m_PlayerNumber; }
		DeviceType GetInputMode()	const { return m_InputMode; }


	private:
		int m_PlayerNumber;

		ControllerButtons m_ControllerInput;
		KeyboardKeys m_KeyboardInput;
		std::shared_ptr<Command> m_Command;
		DeviceType m_InputMode;
	};
}
#endif
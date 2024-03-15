#ifndef ACTION
#define ACTION

#include <memory>
#include "Command.h"
#include "Controller.h"
#include "Keyboard.h"
#include <SDL_scancode.h>

namespace dae
{
	class Action
	{
	public:
		enum class InputMode 
		{
			Controller,
			Keyboard,
			Both
		};

		Action(const Controller::Buttons& controllerButton, std::shared_ptr<Command> command, int const playerNumber);
		Action(const Keyboard::Buttons& keyboardKey, std::shared_ptr<Command> command, int const playerNumber);

		void Execute();

		Controller::Buttons GetButton()			const { return m_ControllerInput; }
		Keyboard::Buttons GetKey()				const { return m_KeyboardInput; }
		//std::shared_ptr<Command> GetCommand()	const { return m_Command; }
		int GetPlayerNumber()					const { return m_PlayerNumber; }
		InputMode GetInputMode()				const { return m_InputMode; }


	private:
		int m_PlayerNumber;

		Controller::Buttons m_ControllerInput;
		Keyboard::Buttons m_KeyboardInput;
		std::shared_ptr<Command> m_Command;
		InputMode m_InputMode;
	};
}
#endif
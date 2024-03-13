#ifndef ACTION
#define ACTION

#include <memory>
#include "Command.h"
#include "Controller.h"

namespace dae
{
	class Action
	{
	public:
		Action(Controller::Buttons controllerButton, std::shared_ptr<Command> command, int const controllerIndex);

		void Execute();

		Controller::Buttons GetButton()			const { return m_ControllerInput; }
		//std::shared_ptr<Command> GetCommand()	const { return m_Command; }
		int GetControllerIndex()				const { return m_ControllerIndex; }

	private:
		Controller::Buttons m_ControllerInput;
		std::shared_ptr<Command> m_Command;
		int m_ControllerIndex;
		//keyboard input keybind
	
	};
}
#endif
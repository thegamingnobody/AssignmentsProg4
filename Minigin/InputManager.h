#pragma once
#include "Singleton.h"


namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	//private:
	//	XINPUT_STATE m_CurrentState;
	};

}

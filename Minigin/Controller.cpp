#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <thread>
#include <iostream>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

class dae::Controller::ControllerImpl
{
public:
	ControllerImpl(int const index)
	{
		ZeroMemory(&m_LastState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		if (index != -1)
		{
			m_PlayerNumber = index;
		}
	}

	void Update()
	{
		CopyMemory(&m_LastState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_PlayerNumber, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_LastState.Gamepad.wButtons;
		buttonChanges;
		//auto buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		//auto buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsButtonPressed(int const button) const { return (m_CurrentState.Gamepad.wButtons & button); }
	int GetPlayerNumber() const { return m_PlayerNumber; }

private:
	int m_PlayerNumber{};
	XINPUT_STATE m_LastState;
	XINPUT_STATE m_CurrentState;
};

dae::Controller::Controller(int const index)
{
	m_Impl = std::make_unique<ControllerImpl>(index);
}

dae::Controller::~Controller()
{
}

void dae::Controller::Update()
{
	m_Impl->Update();
}

bool dae::Controller::IsButtonPressed(int const button) const
{
	return m_Impl->IsButtonPressed(button);
}

int dae::Controller::GetPlayerNumber() const
{
	return m_Impl->GetPlayerNumber();
}

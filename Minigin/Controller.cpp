#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <thread>
#include <iostream>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

class Controller::ControllerImpl
{
public:
	ControllerImpl(int const index)
	{
		ZeroMemory(&m_LastState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		if (index != -1)
		{
			m_ControllerIndex = index;
		}
	}

	void Update()
	{
		CopyMemory(&m_LastState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_LastState.Gamepad.wButtons;
		auto buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		auto buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		if (buttonsPressedThisFrame & XINPUT_GAMEPAD_A)
		{
			std::cout << std::fixed << buttonsPressedThisFrame << "\n";
		}
		if (buttonsReleasedThisFrame & XINPUT_GAMEPAD_A)
		{
			std::cout << std::fixed << buttonsReleasedThisFrame << "\n";
		}
			
	}
private:
	void MoveCursorToBeginning()
	{
		COORD pos = { 0, 10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	int m_ControllerIndex{};
	XINPUT_STATE m_LastState;
	XINPUT_STATE m_CurrentState;
};

Controller::Controller(int const index)
{
	m_Impl = std::make_unique<ControllerImpl>(index);
}

Controller::~Controller()
{
}

void Controller::Update()
{
	m_Impl->Update();
}

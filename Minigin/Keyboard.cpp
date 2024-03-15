#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SDL.h>

#include "Keyboard.h"

class dae::Keyboard::KeyboardImpl
{
public:
	KeyboardImpl(int const index)
	{
		ZeroMemory(&m_LastState, sizeof(Uint8*));
		ZeroMemory(&m_CurrentState, sizeof(Uint8*));
		if (index != -1)
		{
			m_PlayerNumber = index;
		}
	}

	void Update()
	{
		CopyMemory(&m_LastState, &m_CurrentState, sizeof(Uint8*));
		auto currentState{ SDL_GetKeyboardState(nullptr) };
		CopyMemory(&m_CurrentState, &currentState, sizeof(Uint8*));
	}

	bool IsButtonPressed(const Buttons& button) const { return (m_CurrentState[static_cast<int>(button)]); }
	int GetPlayerNumber() const { return m_PlayerNumber; }
private:
	int m_PlayerNumber{};
	Uint8* m_LastState;
	Uint8* m_CurrentState;
};

dae::Keyboard::Keyboard(int const index)
{
	m_Impl = std::make_unique<KeyboardImpl>(index);
}

dae::Keyboard::~Keyboard()
{
}

void dae::Keyboard::Update()
{
	m_Impl->Update();
}

bool dae::Keyboard::IsButtonPressed(const Buttons& button) const
{
	return m_Impl->IsButtonPressed(button);
}

int dae::Keyboard::GetKeyboardIndex() const
{
	return m_Impl->GetPlayerNumber();
}

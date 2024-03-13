#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

int dae::InputManager::AddController()
{
	int const newControllerId = static_cast<int>(m_Controllers.size());
	m_Controllers.emplace_back(std::make_unique<Controller>(newControllerId));

	return newControllerId;
}

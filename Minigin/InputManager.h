#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		int AddController();

	private:
		std::vector<std::unique_ptr<Controller>> m_Controllers;
	};

}

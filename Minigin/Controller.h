#ifndef CONTROLLER
#define CONTROLLER
#include <memory>

namespace dae
{
	class Controller
	{
	public:
		enum class Buttons
		{
			DpadUp			= 0x0001,
			DpadDown		= 0x0002,
			DpadLeft		= 0x0004,
			DpadRight		= 0x0008,

			Start			= 0x0010,
			Select			= 0x0020,
			StickLeft		= 0x0040,
			StickRight		= 0x0080,
		
			ShoulderLeft	= 0x0100,
			ShoulderRight	= 0x0200,

			A				= 0x1000,	//These are the xbox buttons, on nintendo systems the names should be:  B	to get the name and value matched  
			B				= 0x2000,	//																		A
			X				= 0x4000,	//																		Y
			Y				= 0x8000,	//																		X
										//todo: make flag to automatically switch between nintendo mode and xbox mode?
		};

		Controller(int const index);
		~Controller();

		void Update();

		bool IsButtonPressed(const Buttons& button) const;
		int GetPlayerNumber() const;

	private: 
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_Impl;
	};

}
#endif 

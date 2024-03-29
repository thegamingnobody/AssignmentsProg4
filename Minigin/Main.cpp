#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

//#define ENABLE_STEAM

#ifdef ENABLE_STEAM

#pragma warning (push)
#pragma warning (disable: 4996)
#include <steam/steam_api.h>
#pragma warning (pop)

#endif // ENABLE_STEAM

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "transform.h"
#include "InputManager.h"
#include "Controller.h"
#include "Keyboard.h"
#include "MoveCommand.h"
#include "CountersCommand.h"

void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto& inputManager = dae::InputManager::GetInstance();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.tga");
	go->AddComponent<dae::Transform>().SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto font = resourceManager.LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::Transform>().SetPosition(80, 20);
	scene.Add(go);

	//fps component
	go = std::make_shared<dae::GameObject>();

	int const fpsSize{ 27 };
	float const fpsOffset{ 5 };
	std::string const testString{ "Test" };
	auto fpsFont{ resourceManager.LoadFont("Lingua.otf", fpsSize) };

	go->AddComponent<dae::TextComponent>(testString, fpsFont);
	go->AddComponent<dae::FPSComponent>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::Transform>().SetPosition(fpsOffset, static_cast<float>(dae::Minigin::m_WindowHeight - fpsOffset - fpsSize));
	scene.Add(go);

	int const playerControllerIndex = inputManager.AddController(dae::Action::DeviceType::Controller);
	
	//peter pepper
	auto goPlayer = std::make_shared<dae::GameObject>();
	goPlayer->AddComponent<dae::TextureComponent>("PeterPepper.png");
	goPlayer->AddComponent<dae::Transform>(dae::Minigin::m_WindowWidth / 2.0f, dae::Minigin::m_WindowHeight / 2.0f);
	auto& counterComp = goPlayer->AddComponent<dae::CounterComponent>();
	counterComp.AddCounter("Lives", 3);
	counterComp.AddCounter("Score", 0);
	scene.Add(goPlayer);

	inputManager.AddAction(dae::ControllerButtons::DpadUp,			dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goPlayer.get(), glm::vec3(  0, -1,  0)), playerControllerIndex);
	inputManager.AddAction(dae::ControllerButtons::DpadDown,		dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goPlayer.get(), glm::vec3(  0,  1,  0)), playerControllerIndex);
	inputManager.AddAction(dae::ControllerButtons::DpadLeft,		dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goPlayer.get(), glm::vec3( -1,  0,  0)), playerControllerIndex);
	inputManager.AddAction(dae::ControllerButtons::DpadRight,		dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goPlayer.get(), glm::vec3(  1,  0,  0)), playerControllerIndex);
	inputManager.AddAction(dae::ControllerButtons::FaceButtonRight, dae::InputType::PressedThisFrame,	std::make_shared<dae::CountersCommand>	(goPlayer.get(), "Lives", -1),			  playerControllerIndex);
	inputManager.AddAction(dae::ControllerButtons::FaceButtonRight, dae::InputType::PressedThisFrame,	std::make_shared<dae::CountersCommand>	(goPlayer.get(), "Score",  1),			  playerControllerIndex);

	int const player2ControllerIndex = inputManager.AddController(dae::Action::DeviceType::Keyboard);

	//mr egg
	auto goEnemy = std::make_shared<dae::GameObject>();
	goEnemy->AddComponent<dae::TextureComponent>("MrEgg.png");
	goEnemy->AddComponent<dae::Transform>();
	auto& counterComp2 = goEnemy->AddComponent<dae::CounterComponent>();
	counterComp2.AddCounter("Lives", 3);
	counterComp2.AddCounter("Score", 0);
	scene.Add(goEnemy);

	inputManager.AddAction(dae::KeyboardKeys::W, dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goEnemy.get(), glm::vec3(  0, -1,  0)), player2ControllerIndex);
	inputManager.AddAction(dae::KeyboardKeys::S, dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goEnemy.get(), glm::vec3(  0,  1,  0)), player2ControllerIndex);
	inputManager.AddAction(dae::KeyboardKeys::A, dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goEnemy.get(), glm::vec3( -1,  0,  0)), player2ControllerIndex);
	inputManager.AddAction(dae::KeyboardKeys::D, dae::InputType::Held,				std::make_shared<dae::MoveCommand>		(goEnemy.get(), glm::vec3(  1,  0,  0)), player2ControllerIndex);
	inputManager.AddAction(dae::KeyboardKeys::E, dae::InputType::PressedThisFrame,	std::make_shared<dae::CountersCommand>	(goEnemy.get(), "Lives", -1),			 player2ControllerIndex);
	inputManager.AddAction(dae::KeyboardKeys::E, dae::InputType::PressedThisFrame,	std::make_shared<dae::CountersCommand>	(goEnemy.get(), "Score",  1),			 player2ControllerIndex);
}



int main(int, char*[]) 
{
#ifdef ENABLE_STEAM
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;
#endif

	dae::Minigin engine("../Data/");
	engine.Run(load);

#ifdef ENABLE_STEAM
	SteamAPI_Shutdown();
#endif
	return 0;
}
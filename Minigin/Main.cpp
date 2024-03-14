#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

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
#include "MoveCommand.h"

void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto& inputManager = dae::InputManager::GetInstance();

	inputManager.AddController();

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
	go->AddComponent<dae::Transform>(fpsOffset, static_cast<float>(dae::Minigin::m_WindowHeight - fpsOffset - fpsSize));
	scene.Add(go);

	//peter pepper
	auto goPlayer = std::make_shared<dae::GameObject>();
	goPlayer->AddComponent<dae::TextureComponent>("PeterPepper.png");
	goPlayer->AddComponent<dae::Transform>(dae::Minigin::m_WindowWidth / 2.0f, dae::Minigin::m_WindowHeight / 2.0f);
	scene.Add(goPlayer);

	inputManager.AddAction(dae::Controller::Buttons::DpadUp,	std::make_shared<dae::MoveCommand>(goPlayer.get(), glm::vec3( 0, -1, 0)), 0);
	inputManager.AddAction(dae::Controller::Buttons::DpadDown,	std::make_shared<dae::MoveCommand>(goPlayer.get(), glm::vec3( 0,  1, 0)), 0);
	inputManager.AddAction(dae::Controller::Buttons::DpadLeft,	std::make_shared<dae::MoveCommand>(goPlayer.get(), glm::vec3(-1,  0, 0)), 0);
	inputManager.AddAction(dae::Controller::Buttons::DpadRight, std::make_shared<dae::MoveCommand>(goPlayer.get(), glm::vec3( 1,  0, 0)), 0);

	//mr egg
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("MrEgg.png");
	go->AddComponent<dae::Transform>();
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
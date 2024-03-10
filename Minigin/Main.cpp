#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
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

void load()
{
	auto& resourceManager = dae::ResourceManager::GetInstance();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(go.get(), "background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(go.get(), "logo.tga");
	go->AddComponent<dae::Transform>(go.get()).SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto font = resourceManager.LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::TextComponent>(go.get(), "Programming 4 Assignment", font);
	go->AddComponent<dae::TextureComponent>(go.get());
	go->AddComponent<dae::Transform>(go.get()).SetPosition(80, 20);
	scene.Add(go);

	//fps component
	go = std::make_shared<dae::GameObject>();

	int const fpsSize{ 27 };
	int const fpsOffset{ 5 };
	std::string const testString{ "Test" };
	auto fpsFont{ resourceManager.LoadFont("Lingua.otf", fpsSize) };

	go->AddComponent<dae::TextComponent>(go.get(), testString, fpsFont);
	go->AddComponent<dae::FPSComponent>(go.get());
	go->AddComponent<dae::TextureComponent>(go.get());
	go->AddComponent<dae::Transform>(go.get()).SetPosition(fpsOffset, static_cast<float>(dae::Minigin::m_WindowHeight - fpsOffset - fpsSize));
	scene.Add(go);

	////base for player
	//auto goWorldOffset = std::make_shared<dae::GameObject>();
	//goWorldOffset->AddComponent<dae::Transform>(goWorldOffset.get()).SetPosition(dae::Minigin::m_WindowWidth / 2.0f, dae::Minigin::m_WindowHeight / 2.0f);
	//scene.Add(goWorldOffset);

	////peter pepper
	//auto goPlayer = std::make_shared<dae::GameObject>();
	//goPlayer->AddComponent<dae::Transform>(goPlayer.get());
	//goPlayer->AddComponent<dae::TextureComponent>(goPlayer.get(), "PeterPepper.png");
	//goPlayer->AddComponent<dae::RotatorComponent>(goPlayer.get(), 3000.0f, 30.0f);
	//goPlayer->SetParent(goWorldOffset.get());
	//scene.Add(goPlayer);

	////mr egg
	//auto goChild = std::make_shared<dae::GameObject>();
	//goChild->AddComponent<dae::TextureComponent>(goChild.get(), "MrEgg.png");
	//goChild->AddComponent<dae::RotatorComponent>(goChild.get(), -2000.0f, 40.0f);
	//goChild->AddComponent<dae::Transform>(goChild.get());
	//goChild->SetParent(goPlayer.get());
	//scene.Add(goChild);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
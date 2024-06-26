#include <SDL.h>

#if _DEBUG
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
#include "Keyboard.h"
#include "MoveCommand.h"
#include "CountersCommand.h"
#include <ServiceLocator.h>
#include <soundSystem.h>
#include <memory>
#include <DAE_SDL_SoundSystem.h>
#include <BoundingBoxComponent.h>


void load()
{
    dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::DAE_SDL_SoundSystem>());

    auto& resourceManager = dae::ResourceManager::GetInstance();
    auto& inputManager = dae::InputManager::GetInstance();

    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    //auto go = std::make_shared<dae::GameObject>("Background");
    //go->AddComponent<dae::TextureComponent>("background.tga");
    //scene.Add(go);

    //go = std::make_shared<dae::GameObject>("DAE Logo");
    //go->AddComponent<dae::TextureComponent>("logo.tga");
    //go->AddComponent<dae::Transform>().SetPosition(216, 180);
    //scene.Add(go);

    auto font = resourceManager.LoadFont("Lingua.otf", 36);
    //go = std::make_shared<dae::GameObject>("P4A text");
    //go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
    //go->AddComponent<dae::TextureComponent>();
    //go->AddComponent<dae::Transform>().SetPosition(80, 20);
    //scene.Add(go);

    auto go = std::make_shared<dae::GameObject>("keyboard ctrls text");
    font = resourceManager.LoadFont("Lingua.otf", 14);
    go->AddComponent<dae::TextComponent>("Use WASD to move Mr. Egg, C to do damage, Z and X to increase score", font);
    go->AddComponent<dae::TextureComponent>();
    go->AddComponent<dae::Transform>().SetPosition(10, 70);
    scene.Add(go);

    go = std::make_shared<dae::GameObject>("gamepad ctrls text");
    go->AddComponent<dae::TextComponent>("Use D-Pad to move Mr. Pepper, X to do damage, A and B to increase score", font);
    go->AddComponent<dae::TextureComponent>();
    go->AddComponent<dae::Transform>().SetPosition(10, 90);
    scene.Add(go);

    //fps component
    go = std::make_shared<dae::GameObject>("fps comp obj");

    int const fpsSize{ 27 };
    float const fpsOffset{ 5 };
    std::string const testString{ "Test" };
    auto fpsFont{ resourceManager.LoadFont("Lingua.otf", fpsSize) };

    go->AddComponent<dae::TextComponent>(testString, fpsFont);
    go->AddComponent<dae::FPSComponent>();
    go->AddComponent<dae::TextureComponent>();
    go->AddComponent<dae::Transform>().SetPosition(fpsOffset, static_cast<float>(dae::Minigin::m_WindowHeight - fpsOffset - fpsSize));
    scene.Add(go);

    //ground

    glm::vec2 topleftLevel{ 112, 53 };

    go = std::make_shared<dae::GameObject>("LevelSprite");
    auto textureSize = go->AddComponent<dae::TextureComponent>("Sprites/Stage1.png").GetSize();
    go->AddComponent<dae::Transform>(topleftLevel.x, topleftLevel.y);
    //go->AddComponent<dae::BoundingBoxComponent>(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y), dae::ObjectType::Platform);
    scene.Add(go);






    int const playerControllerIndex = inputManager.AddController(dae::Action::DeviceType::Controller);

    int const player2ControllerIndex = inputManager.AddController(dae::Action::DeviceType::Keyboard);

    //peter pepper
    auto goPlayer = std::make_shared<dae::GameObject>("Player", player2ControllerIndex);
    textureSize = goPlayer->AddComponent<dae::TextureComponent>("Sprites/PeterPepper.png").GetSize();

    goPlayer->AddComponent<dae::Transform>(topleftLevel.x, topleftLevel.y - textureSize.y);
    goPlayer->AddComponent<dae::BoundingBoxComponent>(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y), dae::ObjectType::Player);

    auto& counterComp = goPlayer->AddComponent<dae::CounterComponent>();
    counterComp.AddCounter("Lives", dae::CounterTypes::Lives, 3, false);
    counterComp.AddCounter("Score", dae::CounterTypes::Score, 0, false);
    scene.Add(goPlayer);

    inputManager.AddAction(dae::KeyboardKeys::W, dae::InputType::Held, std::make_shared<dae::MoveCommand>(player2ControllerIndex, glm::vec3(0, -1, 0)), player2ControllerIndex);
    inputManager.AddAction(dae::KeyboardKeys::S, dae::InputType::Held, std::make_shared<dae::MoveCommand>(player2ControllerIndex, glm::vec3(0, 1, 0)), player2ControllerIndex);
    inputManager.AddAction(dae::KeyboardKeys::A, dae::InputType::Held, std::make_shared<dae::MoveCommand>(player2ControllerIndex, glm::vec3(-1, 0, 0)), player2ControllerIndex);
    inputManager.AddAction(dae::KeyboardKeys::D, dae::InputType::Held, std::make_shared<dae::MoveCommand>(player2ControllerIndex, glm::vec3(1, 0, 0)), player2ControllerIndex);
    //inputManager.AddAction(dae::KeyboardKeys::C, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(player2ControllerIndex, "Lives", -1), player2ControllerIndex);
    //inputManager.AddAction(dae::KeyboardKeys::Z, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(player2ControllerIndex, "Score", 10), player2ControllerIndex);
    //inputManager.AddAction(dae::KeyboardKeys::X, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(player2ControllerIndex, "Score", 100), player2ControllerIndex);

    //mr egg
    auto goEnemy = std::make_shared<dae::GameObject>("enemy", playerControllerIndex);
    textureSize = goEnemy->AddComponent<dae::TextureComponent>("Sprites/MrEgg.png").GetSize();

    //todo: rethink world location / local pos
    goEnemy->AddComponent<dae::Transform>(dae::Minigin::m_WindowWidth * 0.40f, dae::Minigin::m_WindowHeight * 0.50f);
    goEnemy->AddComponent<dae::BoundingBoxComponent>(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y), dae::ObjectType::Enemy);
    auto& counterComp2 = goEnemy->AddComponent<dae::CounterComponent>();
    counterComp2.AddCounter("Lives", dae::CounterTypes::Lives, 3, false);
    counterComp2.AddCounter("Score", dae::CounterTypes::Score, 0, false);
    scene.Add(goEnemy);

    inputManager.AddAction(dae::ControllerButtons::DpadUp, dae::InputType::Held, std::make_shared<dae::MoveCommand>(playerControllerIndex, glm::vec3(0, -1, 0)), playerControllerIndex);
    inputManager.AddAction(dae::ControllerButtons::DpadDown, dae::InputType::Held, std::make_shared<dae::MoveCommand>(playerControllerIndex, glm::vec3(0, 1, 0)), playerControllerIndex);
    inputManager.AddAction(dae::ControllerButtons::DpadLeft, dae::InputType::Held, std::make_shared<dae::MoveCommand>(playerControllerIndex, glm::vec3(-1, 0, 0)), playerControllerIndex);
    inputManager.AddAction(dae::ControllerButtons::DpadRight, dae::InputType::Held, std::make_shared<dae::MoveCommand>(playerControllerIndex, glm::vec3(1, 0, 0)), playerControllerIndex);
    //inputManager.AddAction(dae::ControllerButtons::FaceButtonLeft, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(playerControllerIndex, "Lives", -1), playerControllerIndex);
    //inputManager.AddAction(dae::ControllerButtons::FaceButtonDown, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(playerControllerIndex, "Score", 10), playerControllerIndex);
    //inputManager.AddAction(dae::ControllerButtons::FaceButtonRight, dae::InputType::PressedThisFrame, std::make_shared<dae::CountersCommand>(playerControllerIndex, "Score", 100), playerControllerIndex);



}

int main(int, char* []) 
{
    dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}
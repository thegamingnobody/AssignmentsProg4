#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <memory>
#include "Transform.h"
#include <string>
#include <vector>
#include "Component.h"
#include <iostream>
#include <optional>
#include "Observer.h"
#include "Event.h"
#include "Subject.h"

namespace dae
{
	template <class... Arguments>
	class Observer;

	class GameObject final
	{
	public:
		void Update(float const elapsedTime);
		void Render() const;

		void SetRenderable(bool const renderable) { m_Render = renderable; }

		void SetParent(GameObject* newParent);
		std::optional<GameObject*> GetParent() const;

		template <class ComponentType, class... Arguments>
		requires std::derived_from<ComponentType, Component>
		ComponentType& AddComponent(Arguments&&... arguments)
		{
			auto createComponent = [this](auto&&... args) {
				auto component = std::make_shared<ComponentType>(this, std::forward<decltype(args)>(args)...);
				m_pComponents.emplace_back(component);
				return component;
				};

			return *createComponent(std::forward<Arguments>(arguments)...);
		}

		template <class ComponentType>
		requires std::derived_from<ComponentType, Component>
		void RemoveComponent()
		{
			for (auto& component : m_pComponents)
			{
				if (auto derivedComponent = dynamic_cast<ComponentType*>(component.get()))
				{
					component->SetShouldBeRemoved();
				}
			}
		}

		template <class ComponentType>
		requires std::derived_from<ComponentType, Component>
		std::optional<ComponentType*> GetComponent() const
		{
			for (auto& component : m_pComponents)
			{
				if (auto derivedComponent = dynamic_cast<ComponentType*>(component.get()))
				{
					return derivedComponent;
				}
			}

			return std::nullopt;
		}



		GameObject(bool const renderable = true);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <class... Arguments>
		void AddObserver(Observer<Arguments...>* observer)
		{
			m_SubjectPlayerDied->AddObserver(observer);
		}
		template <class... Arguments>
		void RemoveObserver(Observer<Arguments...>* observer)
		{
			m_SubjectPlayerDied->RemoveObserver(observer);
		}

		template <class... Arguments>
		void Notify(Event<Arguments...> event)
		{
			switch (event.m_type)
			{
			case dae::EventType::PlayerDied:
				std::cout << std::get<0>(event.m_args) << " " << std::get<1>(event.m_args) << "\n";
				m_SubjectPlayerDied->NotifyObservers(event.m_args);
				break;
			default:
				break;
			}
		}


	private:
		GameObject* m_pOwnerObject{ nullptr };
		std::vector<GameObject*> m_pChildObjects{};

		std::vector<std::shared_ptr<Component>> m_pComponents{};
		bool m_Render{ true };

		//wanted to remove template brackets from Subject here, but haven't figured out how
		Subject<const std::string&, int const>* m_SubjectPlayerDied;
	};
}
#endif

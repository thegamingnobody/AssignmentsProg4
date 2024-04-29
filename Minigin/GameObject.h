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

		template <class ComponentType>
		requires std::derived_from<ComponentType, Component>
		bool HasComponent() const
		{
			std::optional<ComponentType*> component{ GetComponent<ComponentType>() };
			return component.has_value();
		}

		GameObject(int const playerNumber = -1, bool const renderable = true);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		int const m_PlayerNumber;
	private:
		GameObject* m_pOwnerObject{ nullptr };
		std::vector<GameObject*> m_pChildObjects{};

		std::vector<std::shared_ptr<Component>> m_pComponents{};

		bool m_Render{ true };
	};
}
#endif

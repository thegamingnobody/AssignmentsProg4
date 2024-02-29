#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <memory>
#include "Transform.h"
#include <string>
#include <vector>
#include "Component.h"
#include <iostream>

namespace dae
{
	class GameObject final
	{
	public:
		void Update(float const elapsedTime);
		void Render() const;

		void SetPosition(float x, float y);

		template <class ComponentType, class... Arguments>
		requires std::derived_from<ComponentType, Component>
		ComponentType& AddComponent(Arguments&&... arguments)
		{
			auto component{ std::make_shared<ComponentType>(std::forward<Arguments>(arguments)...) };
			m_pComponents.emplace_back(component);

			return *component;
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

			for (auto& it { m_pComponents.begin()}; it != m_pComponents.end(); it)
			{
				if ((*it)->GetSouldBeRemoved())
				{
					it = m_pComponents.erase(it);
				}
			}
		}

		template <class ComponentType>
		requires std::derived_from<ComponentType, Component>
		ComponentType& GetComponent()
		{
			for (auto& component : m_pComponents)
			{
				if (auto derivedComponent = dynamic_cast<ComponentType*>(component.get()))
				{
					return *derivedComponent;
				}
			}

			throw std::runtime_error("Component not found");
		}

		GameObject(bool const renderable = true);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SetRenderable(bool const renderable) { m_Render = renderable; }

	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<Component>> m_pComponents{};
		bool m_Render{ true };
	};
}
#endif

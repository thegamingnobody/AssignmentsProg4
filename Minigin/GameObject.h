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
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float const elapsedTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <class ComponentType, class... Arguments>
		requires std::derived_from<ComponentType, Component>
		ComponentType& AddComponent(Arguments&&... arguments)
		{
			auto component{ std::make_shared<ComponentType>(std::forward<Arguments>(arguments)...) };
			m_pComponents.emplace_back(component);

			component.get()->SetOwnerObject(std::make_shared<GameObject>());

			return *component;
		}

		//template <class ComponentType>
		//requires std::derived_from<ComponentType, Component>
		//bool RemoveComponent()
		//{
		//	for (auto& component : m_pComponents)
		//	{
		//		if (typeid(component) == typeid(ComponentType))
		//		{
		//			std::cout << "Remove\n";
		//			return true;
		//		}
		//	}
		//	return false;
		//}

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
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SetRenderable(bool const renderable) { m_Render = renderable; }

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<Component>> m_pComponents{};
		bool m_Render{ true };
	};
}
#endif

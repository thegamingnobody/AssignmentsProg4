#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <memory>
#include "Transform.h"
#include <string>
#include <vector>
#include "Component.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <typename T>
		void AddComponent(T* component) 
		{
			m_pComponents.emplace_back(std::make_unique<T>(component));
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

		std::vector<std::unique_ptr<Component>> m_pComponents{};
		bool m_Render{ true };
	};
}
#endif

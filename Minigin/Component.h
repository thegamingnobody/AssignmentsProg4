#ifndef COMPONENT
#define COMPONENT

#include <memory>
#include "Texture2D.h"

namespace dae
{
	class GameObject;

	class Component 
	{
	public:
		virtual void Update(float const elapsedTime);
		virtual void Render() const;

		virtual std::shared_ptr<dae::Texture2D> GetTexture() = 0;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator= (const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		dae::GameObject* m_pGameObject{};
	protected:
		Component(dae::GameObject* object);
		dae::GameObject* GetOwner() const;
	};
}
#endif
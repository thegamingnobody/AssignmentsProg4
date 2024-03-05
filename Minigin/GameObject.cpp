#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "TextureComponent.h"

dae::GameObject::GameObject(bool const renderable) : 
	m_pOwnerObject(nullptr)
{
	m_Render = renderable;
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float const elapsedTime)
{
	for (auto& component : m_pComponents)
	{
		component->Update(elapsedTime);
	}

	for (auto it{ m_pComponents.begin() }; it != m_pComponents.end(); it)
	{
		if ((*it)->GetSouldBeRemoved())
		{
			it = m_pComponents.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void dae::GameObject::Render() const
{
	if (not m_Render) return;

	for (auto& component : m_pComponents)
	{
		if (auto derivedComponent = dynamic_cast<dae::TextureComponent*>(component.get()))
		{
			derivedComponent->Render();
		}
	}
}

void dae::GameObject::SetParent(GameObject* newParent)
{
	//check if new parent is valid
	if (newParent == nullptr or newParent == this) return;

	//remove child from old parent
	if (m_pOwnerObject)
	{
		auto it = std::find(m_pOwnerObject->m_pChildObjects.begin(), m_pOwnerObject->m_pChildObjects.end(), this);

		if (it != m_pOwnerObject->m_pChildObjects.end())
		{
			m_pOwnerObject->m_pChildObjects.erase(it);
		}
	}

	//set new parent
	m_pOwnerObject = newParent;

	//add to parent as child
	m_pOwnerObject->m_pChildObjects.emplace_back(this);
}

std::optional<dae::GameObject*> dae::GameObject::GetParent() const
{
	if (m_pOwnerObject == nullptr)
	{
		return std::nullopt;
	}
	
	return m_pOwnerObject;
}
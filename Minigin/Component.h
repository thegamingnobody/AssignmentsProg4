#ifndef COMPONENT
#define COMPONENT

#include <memory>

namespace dae
{
	class GameObject;
}

class Component 
{
public:
	void SetOwnerObject(std::shared_ptr<dae::GameObject> object);
	std::shared_ptr<dae::GameObject> GetOwner() const;
private:
	//Component(std::shared_ptr<dae::GameObject> gameObject);
protected:
	std::shared_ptr<dae::GameObject> m_pGameObject{};
};
#endif
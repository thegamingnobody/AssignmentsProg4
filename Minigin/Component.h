#ifdef COMPONENT
#endif
#define COMPONENT

#include <memory>
#include "GameObject.h"

class Component 
{
public:
	
protected:
	std::shared_ptr<dae::GameObject> m_pGameObject{};
};
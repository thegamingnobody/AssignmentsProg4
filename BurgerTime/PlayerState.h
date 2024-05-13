#ifndef DAE_PLAYERSTATE
#define DAE_PLAYERSTATE

#include "GameObject.h"

namespace dae
{
	class PlayerState
	{
	public:
		PlayerState(std::shared_ptr<GameObject> object);

		virtual void OnEnter() {}
		virtual void OnExit() {}

	private:
		std::shared_ptr<GameObject> m_Object;
	};
}

#endif
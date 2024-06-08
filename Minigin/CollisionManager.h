#pragma once
#include "Singleton.h"
#include <vector>
#include "BoundingBoxComponent.h"
#include "Event.h"



namespace dae
{
	class CollisionManager : public Singleton<CollisionManager>
	{
	public:

		void Init();

		void RegisterBB(BoundingBoxComponent* BB);

		void CheckCollision();

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;

		bool AreColliding(BoundingBoxComponent* box1, BoundingBoxComponent* box2);

		std::vector<BoundingBoxComponent*> m_BoundingBoxes;
		int m_NextId;
	};
}


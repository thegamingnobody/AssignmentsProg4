#pragma once
#include "Singleton.h"
#include <vector>
#include "BoundingBoxComponent.h"
#include "Event.h"
#include <map>



namespace dae
{
	struct CollisionInfo
	{
		bool ResetX;
		bool ResetY;
	};


	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		typedef std::tuple<ObjectType, ObjectType> ObjectTuple;


		void Init();

		void RegisterBB(BoundingBoxComponent* BB);

		void CheckCollision();

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;

		bool AreColliding(BoundingBoxComponent* box1, BoundingBoxComponent* box2);

		std::vector<BoundingBoxComponent*> m_BoundingBoxes;
		int m_NextId;

		std::map<ObjectTuple, CollisionInfo> m_CollisionInfoMap;
	};
}


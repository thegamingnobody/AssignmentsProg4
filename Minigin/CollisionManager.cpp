#include "CollisionManager.h"

void dae::CollisionManager::Init()
{
    m_NextId = 0;

    dae::CollisionInfo collisionInfo;

    collisionInfo.ResetX = false;
    collisionInfo.ResetY = true;
    m_CollisionInfoMap[std::make_tuple(ObjectType::Player, ObjectType::Platform)] = collisionInfo;

    collisionInfo.ResetX = true;
    collisionInfo.ResetY = false;
    m_CollisionInfoMap[std::make_tuple(ObjectType::Player, ObjectType::Ladder)] = collisionInfo;
}

void dae::CollisionManager::RegisterBB(dae::BoundingBoxComponent* BB)
{
	m_BoundingBoxes.emplace_back(BB);
    BB->SetId(m_NextId++);
}

void dae::CollisionManager::CheckCollision()
{
    for (auto& box1 : m_BoundingBoxes)
    {
        if (not box1->GetMovedThisFrame()) continue;

        box1->SetMovedThisFrame(false);

        for (auto& box2 : m_BoundingBoxes)
        {
            if (AreColliding(box1, box2))
            {
                auto collisionInfo = m_CollisionInfoMap.find(std::make_tuple(ObjectType::Player, ObjectType::Platform))->second;
                box1->ResetDirectionThisFrame(collisionInfo.ResetX, collisionInfo.ResetY);
                box2->ResetDirectionThisFrame(true, true);
                std::cout << "Collision\n";
            }
        }
    }
}

bool dae::CollisionManager::AreColliding(dae::BoundingBoxComponent* box1, dae::BoundingBoxComponent* box2)
{
    if (box1->GetId() == box2->GetId()) return false;

    auto rect1{ box1->GetBoundingBox() };
    auto rect2{ box2->GetBoundingBox() };

    if (rect1.x + rect1.width <= rect2.x or rect2.x + rect2.width <= rect1.x) return false;
    
    if (rect1.y + rect1.height <= rect2.y or rect2.y + rect2.height <= rect1.y) return false;

    return true;
}

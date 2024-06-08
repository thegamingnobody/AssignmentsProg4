#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
    struct Rect
    {
        float x;
        float y;
        float width;
        float height;
    };



    class BoundingBoxComponent : public Component, public Observer
    {
    public:
        BoundingBoxComponent(dae::GameObject* object, float const width, float const height);
        virtual ~BoundingBoxComponent() override = default;
        BoundingBoxComponent(const BoundingBoxComponent& other) = delete;
        BoundingBoxComponent(BoundingBoxComponent&& other) = delete;
        BoundingBoxComponent& operator= (const BoundingBoxComponent& other) = delete;
        BoundingBoxComponent& operator=(BoundingBoxComponent&& other) = delete;

        void Notify(const Event& event) override;

        Rect& GetBoundingBox();

        int GetId() const { return m_BoxId; }
        void SetId(int const id) { m_BoxId = id; }

        bool GetMovedThisFrame() const { return m_MovedThisFrame; }
        void SetMovedThisFrame(bool movedFrame) { m_MovedThisFrame = movedFrame; }
        
        void ResetDirectionThisFrame(bool const resetX, bool const resetY);
    private:
        Rect m_BoundingBox;

        int m_BoxId;
        bool m_MovedThisFrame;
    };
}



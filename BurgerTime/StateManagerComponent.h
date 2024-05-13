#ifndef DAE_STATEMANAGERCPNT
#define DAE_STATEMANAGERCPNT

#include <Component.h>
#include <Observer.h>
#include "PlayerState.h"

namespace dae
{
    class StateManagerComponent : public Component, public Observer
    {
    public:
        void Update(float const elapsedTime) override;

        StateManagerComponent(dae::GameObject* object);

        void Notify(const Event& event) override;

    private:

    };
}

#endif
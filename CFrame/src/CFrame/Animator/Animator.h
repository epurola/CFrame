#pragma once
#include "../UIElements/UIElement.h"

enum class AnimationEndBehavior {
    None = 0,
    Reset = 1,
    Hold = 2,
    Reverse = 3,
    Infinite = 4
};

namespace CFrame 
{
    class Animator 
    {
    public:
        virtual ~Animator() = default;
        virtual void Update(float timestep) = 0;
        virtual bool IsAnimating() const = 0;
    };
}
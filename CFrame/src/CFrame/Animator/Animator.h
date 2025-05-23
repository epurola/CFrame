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
        void SetOnEnd(std::function<void()> onEnd) { this->onEnd = onEnd; }

    protected:
       // virtual bool AnimationEndEvent();

    protected:
        std::function<void()> onEnd = nullptr;
    };
}
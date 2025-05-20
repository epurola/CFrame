#pragma once
#include "../UIElements/UIElement.h"

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
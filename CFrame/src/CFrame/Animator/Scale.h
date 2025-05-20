#pragma once
#include "Animator.h"

namespace CFrame 
{
    class Scale : public Animator 
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startScale = 1.0f;
        float endScale = 1.0f;
        bool animating = false;

        UIElement& element;

        Scale(float start, float end, float duration, UIElement& element)
            : duration(duration), startScale(start), endScale(end), animating(true),
        element(element){}

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}



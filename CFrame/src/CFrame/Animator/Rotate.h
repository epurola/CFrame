#pragma once
#include "Animator.h"

namespace CFrame
{
    class Rotate : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startAngle = 1.0f;
        float endAngle = 1.0f;
        bool animating = false;
        AnimationEndBehavior ending;
        UIElement& element;

        Rotate(float start, float end, float duration, AnimationEndBehavior ending, UIElement& element)
            : duration(duration), startAngle(start), ending(ending), endAngle(end), animating(true), 
            element(element) {
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
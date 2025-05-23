#pragma once
#include "Animator.h"

namespace CFrame
{
    class ScaleY : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startScale = 1.0f;
        float endScale = 1.0f;
        bool animating = false;
        float originalScale = 1.0f;
        AnimationEndBehavior end;

        UIElement& element;

        ScaleY(float start, float end, float duration, AnimationEndBehavior ending, UIElement& element)
            : duration(duration), startScale(start), endScale(end), end(ending), animating(true),
            element(element)
        {
            originalScale = element.GetProperties().scaleY;
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
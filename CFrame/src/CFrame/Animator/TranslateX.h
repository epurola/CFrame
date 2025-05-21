#pragma once
#include "Animator.h"

namespace CFrame
{
    class TranslateX : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startPos = 1.0f;
        float endPos = 1.0f;
        bool animating = false;
        AnimationEndBehavior ending;
        float originalX = 1.0f;

        UIElement& element;

        TranslateX(float distance, float duration, AnimationEndBehavior reset, UIElement& element)
            : duration(duration), animating(true), ending(reset), element(element) {
            startPos = element.GetX();
            endPos = startPos + distance;
            originalX = element.GetX();
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
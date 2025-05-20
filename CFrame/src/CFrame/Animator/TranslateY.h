#pragma once
#include "Animator.h"

namespace CFrame
{
    class TranslateY : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startPos = 1.0f;
        float endPos = 1.0f;
        bool animating = false;

        UIElement& element;

        TranslateY(float distance, float duration, UIElement& element)
            : duration(duration), animating(true), element(element) {
            startPos = element.GetY();
            endPos = startPos + distance;
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
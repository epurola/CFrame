#pragma once
#include "Animator.h"

namespace CFrame
{
    class Translate : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        float startX = 1.0f;
        float startY = 1.0f;
        float endX = 1.0f;
        float endY = 1.0f;
        bool animating = false;
        float originalX = 1.0f;
        float originalY = 1.0f;
        AnimationEndBehavior reset;

        UIElement& element;

        Translate(float distanceX, float distanceY,float duration, AnimationEndBehavior reset, UIElement& element)
            : duration(duration), animating(true), reset(reset), element(element) {
            startX = element.GetX();
            endX = startX + distanceX;
            startY = element.GetY();
            endY = startY + distanceY;
            originalX = element.GetX();
            originalY = element.GetY();
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
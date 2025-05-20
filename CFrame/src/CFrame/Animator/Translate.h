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

        UIElement& element;

        Translate(float distanceX, float distanceY,float duration, UIElement& element)
            : duration(duration), animating(true), element(element) {
            startX = element.GetX();
            endX = startX + distanceX;
            startY = element.GetY();
            endY = startY + distanceY;
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }
    };
}
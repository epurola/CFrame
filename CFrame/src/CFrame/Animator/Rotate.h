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

        Rotate(float start, float end, float duration)
            : duration(duration), startAngle(start), endAngle(end), animating(true) {
        }

        void Update(float timestep, UIElement& element) override;
        bool IsAnimating() const override { return animating; }
    };
}
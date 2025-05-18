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

        Scale(float start, float end, float duration)
            : duration(duration), startScale(start), endScale(end), animating(true) {
        }

        void Update(float timestep, UIElement& element) override;
        bool IsAnimating() const override { return animating; }
    };
}



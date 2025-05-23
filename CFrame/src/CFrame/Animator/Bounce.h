#pragma once
#include "Animator.h"
#include "TranslateY.h"
#include "Scale.h"
#include <memory>
#include "ScaleY.h"

namespace CFrame
{

    class Bounce : public Animator
    {
    public:
        float duration;
        float elapsed = 0.0f;
        bool animating = false;
        float phase1 = 0.0f;
        float phase2 = 0.0f;
        float phase3 = 0.0f;
        AnimationEndBehavior ending;
        UIElement& element;
        bool finished = false;

        Bounce( UIElement& element)
           : animating(true),  element(element) 
        {
            StartPhase1();
        }

        void Update(float timestep) override;
        bool IsAnimating() const override { return animating; }

    private: 
        Animator* current;

        void StartPhase1() {
            auto* anim = new TranslateY(20.0f, 0.3f, AnimationEndBehavior::None, element);
            anim->SetOnEnd([this]() {
                StartPhase2();
                });
        
            element.StartAnimation(anim);
        }

        void StartPhase2() {
            auto* anim = new Scale(1.0f, 1.05f, 0.15f, AnimationEndBehavior::Reverse, element);

            anim->SetOnEnd([this]() {
                StartPhase3();
              });
            
            element.StartAnimation(anim);
            element.StartAnimation<ScaleY>(1.0f, 0.9f, 0.15f, AnimationEndBehavior::None);
        }

        void StartPhase3() {
            auto* anim = new TranslateY(-20.0f, 0.3f, AnimationEndBehavior::None, element);
            anim->SetOnEnd([this]() {
                StartPhase1(); // loop
                });
            element.StartAnimation(anim);
        }
        

    };

}
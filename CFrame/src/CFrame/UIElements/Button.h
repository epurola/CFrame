#pragma once
#include <string>
#include <functional>
#include "UIElement.h"
#include <memory> 

#include "../Animator/Animator.h"

namespace CFrame 
{
    class CFRAME_API Button : public UIElement 
    {
    public:
        Button(int x , int y , int w , int h , const std::string& text = "Button", 
            std::function<void()> onClick =  []() {},
            std::function<void()> onHover = []() {},
            UIElement* parent = nullptr);


        explicit Button(int w, int h)
            : Button(0, 0, w, h, "Button", nullptr) {
        }

        ~Button();

        void Render(Renderer& renderer) override;
        void OnEvent(CFrameEvent& event) override;
        void SetOnHover(std::function<void()> onHover);
        void SetOnClick(std::function<void()> onClick);
        void SetOnLeave(std::function<void()> onLeave);

        inline ElementType GetElementType() const override { return ElementType::BUTTON; };
      

    private:
        //Color color;
        std::function<void()> onClick;
        std::function<void()> onHover;
        std::function<void()> onLeave = []() {};
        std::string text;
        std::unique_ptr<Animator> animator;
        bool hovering = false;
    };
}
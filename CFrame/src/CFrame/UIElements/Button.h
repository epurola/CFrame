#pragma once
#include <string>
#include <functional>
#include "UIElement.h"

namespace CFrame 
{
    class CFRAME_API Button : public UIElement 
    {
    public:
        Button(int x=0, int y = 0, int w =-1, int h =-1, const std::string& text = "Button", std::function<void()> onClick = nullptr, UIElement* parent = nullptr);
        ~Button();

        void Render(Renderer& renderer) override;
        void OnEvent(CFrameEvent& event) override;
      

    private:
        //Color color;
        std::function<void()> onClick;
        std::string text;
    };
}
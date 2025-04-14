#pragma once
#include <string>
#include <functional>
#include "UIElement.h"
#include <memory> 
#include "../Animator/Animator.h"
#include <map>



namespace CFrame 
{
    class CFRAME_API Button : public UIElement 
    {
    public:
        Button(int x , int y , int w , int h , const std::string& text = "Button", 
            std::function<void()> onClick =  []() {},
            UIElement* parent = nullptr);


        explicit Button(int w, int h)
            : Button(0, 0, w, h, "Button", nullptr) {
        }

        ~Button();

        void Render(Renderer& renderer) override;
        void UpdateChildSizes() override; 
        void OnEvent(CFrameEvent& event) override;
        void SetOnClick(std::function<void()> onClick);
        void StartAnimation();

        void SetText(std::string text);
        void setTextOpacity(float opacity);
        void SetFontSize(float size);
        void SetTextAlign(TextAlign alignX);
        

        inline ElementType GetElementType() const override { return ElementType::BUTTON; };
       
    private:
        
        std::function<void()> onClick;
        std::string text;
        std::unique_ptr<Animator> animator;
        bool hovering = false;
        std::shared_ptr<Texture> labelTexture;
        TextProperties textProps;
        std::map<char, fontInfo> glyphs;
        std::unique_ptr<FontLoader> fontLoader;
    };
}
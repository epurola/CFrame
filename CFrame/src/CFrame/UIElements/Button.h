#pragma once
#include <string>
#include <functional>
#include "UIElement.h"
#include <memory> 
#include "../Animator/Animator.h"
#include <map>
#include <optional>


namespace CFrame 
{
    class CFRAME_API Button : public UIElement 
    {
    public:
        Button( int x , int y , int w , int h , const std::string& text = "Button", 
            std::function<void()> onClick =  []() {},
            UIElement* parent = nullptr);

        explicit Button( int w, int h) 
            : Button(0, 0, w, h, "Button", nullptr) { }

        ~Button();

        void Render(Renderer& renderer) override;
        void UpdateChildSizes() override; 
        void OnEvent(CFrameEvent& event) override;
        void RegisterAnimator(std::shared_ptr<ApplicationManager> manager) override;
        void SetOnClick(std::function<void()> onClick);
        void StartAnimation();

        void SetText(std::string text);
        void SetIcon(int codePoint);
        void setTextOpacity(float opacity);
        void SetFontSize(float size);
        void SetFont(Font font);
        
        inline ElementType GetElementType() const override { return ElementType::BUTTON; };
       
    private:
        std::function<void()> onClick;
        std::string text;
        std::optional<int> icon = std::nullopt;
        std::unique_ptr<Animator> animator;
        bool hovering = false;
        std::shared_ptr<Texture> atlasTexture;
        std::map<char, fontInfo> glyphs;

        float atlasWidth = 0.0f;
        float atlasHeight = 0.0f;

    private:
        bool HandleMouseButtonDown(MouseButtonDownEvent& e);
        bool HandleMouseLeaveWindow();
        bool HandleMouseMove(MouseMovedEvent& e);

        void InitAtlasTexture();
        void SetOverFlowProperties();
    };
}
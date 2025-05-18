#pragma once
#include <string>
#include <functional>
#include "UIElement.h"
#include <memory> 
#include <map>
#include <optional>
#include "../Renderer/Renderer1.h"


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

        void Render(Renderer1& renderer) override;
        void Render(float timestep) override;
        void UpdateChildSizes() override; 
        void OnEvent(CFrameEvent& event) override;
        void RegisterAnimator(std::shared_ptr<ApplicationManager> manager) override;
        void SetOnClick(std::function<void()> onClick);

        void SetText(std::string text);
        void SetIcon(int codePoint);
        void setTextOpacity(float opacity);
        void SetFontSize(float size);
        void SetFont(Font font);
        
        inline ElementType GetElementType() const override { return ElementType::BUTTON; };
    protected:
        bool MouseDragEvent(MouseDraggedEvent& event) override;
        bool MousePressEvent(MouseButtonDownEvent& event) override;
        bool MouseReleaseEvent(MouseButtonReleasedEvent& event) override;
        bool MouseMoveEvent(MouseMovedEvent& event) override;
        bool MouseLeaveEvent() override;
       
    private:
        std::function<void()> onClick;
        std::string text;
        std::optional<int> icon = std::nullopt;
        bool hovering = false;
        std::shared_ptr<Texture> atlasTexture;
        std::map<char, fontInfo> glyphs;

        float atlasWidth = 0.0f;
        float atlasHeight = 0.0f;

    private:
        bool HandleMouseLeaveWindow();

        void InitAtlasTexture();
        void SetOverFlowProperties();
    };
}
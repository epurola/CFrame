#pragma once
#include <vector>
#include "../Core.h"
#include "../Renderer/Renderer.h"
#include "../CFrameEvent/CFrameEvent.h"
#include "Color.h"

namespace CFrame 
{

    struct ElementProperties 
    {
        int marginLeft = 0;
        int marginRight = 0;
        int marginTop = 0;
        int marginBottom = 0;
        int padding = 0;
        int radius = 0;
        float scaleX = 1;
        float scaleY = 1;
        float animScaleX = 1;
        float animScaleY = 1;
        float duration = 0.0f;
    };
    enum ElementType
    {
        CONTAINER,
        BUTTON
    };

    class CFRAME_API UIElement {

    public:
        UIElement(int x = 0, int y = 0, int w = -1, int h = -1, UIElement* parent = nullptr);
        virtual ~UIElement() = default;

        virtual void Render(Renderer& renderer) = 0;

        virtual void UpdateChildSizes() {}

        virtual void OnEvent(CFrameEvent& event) = 0;

        virtual ElementType GetElementType() const = 0;

        void SetMargin(int marginleft, int marginRight, int marginTop, int marginBottom);
        void SetPadding(int padding);
        void SetParent(UIElement* p);
        void SetRadius(int r);
        void SetHeight(int h);
        void SetWidth(int w);
        void SetX(int x);
        void SetY(int y);
        /// Sets the color of the UI element.
        /// @param color.
        /// The format is {r,g,b,a}. You can set a custom color using this format.
        void SetColor(Color color);
        void SetGradient(Color color1, Color color2);
        void SetScale(float scaleX, float scaleY, float duration = 0.0);
        void AnimateScale(float scaleX, float scaleY);

        inline int GetX() const { return x; }
        inline int GetY() const { return y; }
        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
        inline bool IsWidthResizable() const { return isWidthResizable; }
        inline bool IsHeightResizable() const { return isHeightResizable; }
        inline bool IsElementWithAnimation() const { return isAnimatedElement; }
        ElementProperties& GetProperties();

        void SetOnHover(std::function<void()> onHover);
        void SetOnLeave(std::function<void()> onLeave);
        

    protected:
        UIElement* parent;  // toDo dont use a raw pointer
        bool isWidthResizable;
        bool isHeightResizable;
        int x, y, width, height;
        Color color;
        Color color2;
        ElementProperties properties;
        bool isAnimatedElement = false;
        std::function<void()> onHover = []() {};
        std::function<void()> onLeave = []() {};
    };

}
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
        float border = 0;
        Color borderColor1;
        Color borderColor2;
        Color color1;
        Color color2;
        float scaleX = 1;
        float scaleY = 1;
    };

    struct AnimationProperties {
        float animScaleX = 1.2;
        float animScaleY = 1.2;
        float duration = 1.0f;
        bool isAnimatedElement = false;
        float speed = 0;
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
        void SetBorder(float border);
        void SetBorderColor(Color color1);
        void SetBorderGradient(Color color1, Color color2);
        /// Sets the color of the UI element.
        /// @param color.
        /// The format is {r,g,b,a}. You can set a custom color using this format.
        void SetColor(Color color);
        void SetGradient(Color color1, Color color2);
        void SetScale(float scaleX, float scaleY);
        void AnimateScale(float scaleX, float scaleY);
        void AnimateGradient(float speed);

        inline int GetX() const { return x; }
        inline int GetY() const { return y; }
        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
        inline float GetBorder() const { return properties.border; }
        inline bool IsWidthResizable() const { return isWidthResizable; }
        inline bool IsHeightResizable() const { return isHeightResizable; }
        inline bool IsElementWithAnimation() const { return animProperties.isAnimatedElement; }
        inline ElementProperties& GetProperties() { return properties; };
        inline AnimationProperties& GetAnimProperties() { return animProperties; };

        void SetOnHover(std::function<void()> onHover);
        void SetOnLeave(std::function<void()> onLeave);
        

    protected:
        UIElement* parent;  // toDo dont use a raw pointer
        int x, y, width, height;
        bool isWidthResizable;
        bool isHeightResizable;
        ElementProperties properties;
        AnimationProperties animProperties;
     
        std::function<void()> onHover = []() {};
        std::function<void()> onLeave = []() {};
    };

}
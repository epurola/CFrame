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
        float scale = 1;
    };

    class CFRAME_API UIElement {

    public:
        UIElement(int x = 0, int y = 0, int w = -1, int h = -1, UIElement* parent = nullptr);
        virtual ~UIElement() = default;

        virtual void Render(Renderer& renderer) = 0;

        virtual void UpdateChildSizes() {}

        virtual void OnEvent(CFrameEvent& event) = 0;

        void SetMargin(int marginleft, int marginRight, int marginTop, int marginBottom);
        void SetPadding(int padding);
        void SetParent(UIElement* p);
        void SetRadius(int r);
        void SetHeight(int h);
        void SetWidth(int w);
        void SetX(int x);
        void SetY(int y);
        void SetColor(Color color);
        void SetScale(float scale);

        inline int GetX() const { return x; }
        inline int GetY() const { return y; }
        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
        inline bool IsWidthResizable() const { return isWidthResizable; }
        inline bool IsHeightResizable() const { return isHeightResizable; }
        ElementProperties& GetProperties();
        

    protected:
        UIElement* parent;  // toDo dont use a raw pointer
        bool isWidthResizable;
        bool isHeightResizable;
        int x, y, width, height;
        Color color;
        ElementProperties properties;
    };

}
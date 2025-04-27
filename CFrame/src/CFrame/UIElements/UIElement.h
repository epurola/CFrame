#pragma once
#include <vector>
#include <cmath>
#include <optional>
#include "../Core.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/FontManager.h"
#include "../CFrameEvent/CFrameEvent.h"
#include "Color.h"
#include "../AnimationManager.h"

namespace CFrame 
{
    class Renderer;

    enum ElementType
    {
        CONTAINER,
        BUTTON,
        LABEL,
        INPUTFIELD
    };

    enum TextAlign {
        Start,
        Center,
        End
    };

    enum class PositionMode {
        TopLeft,
        TopRight, // Not used
        BottomLeft,
        BottomRight,// Not used

    };

    struct Point {
        int x;
        int y;
    };

    struct Radius {
        float topRight    = 0;
        float topLeft     = 0;
        float bottomLeft  = 0;
        float bottomRight = 0;
    };

    struct TextProperties  
    {  
       std::vector<float> vertices;  
       std::vector<unsigned int> indices;  
       float offsetX = 0.0f; 
       float offsetY = 0.0f; 
       int textWidth = 0, textHeight = 0;  
       float opacity = 1;  
       float fontSize = 24;  
       TextAlign textAlign = TextAlign::Center;
       Font font = Font::Verdana;
       Color color1 = Color::White;
       Color color2 = Color::White;
    };

    struct OverFlowProperties {
        bool overflow = false;
        int clipY;
        int clipHeight;
        int clipX;
        int clipWidth;
    };

    struct Vertices {
        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
    };

    struct LineProperties {
        Vertices vertices;
        int width;
        int height;
        Color color;
    };


    struct ElementProperties 
    {
        int marginLeft     = 0;
        int marginRight    = 0;
        int marginTop      = 0;
        int marginBottom   = 0;
        int padding        = 0;
        Radius radius;
        Vertices vertices;
        float border       = 0;
        float borderTop    = 0;
        float borderBottom = 0;
        float borderLeft   = 0;
        float borderRight  = 0;
        Color borderColor1;
        Color borderColor2;
        Color color1;
        Color color2;
        float scaleX       = 1;
        float scaleY       = 1;
        float angle        = 0.0f;
        float opacity      = 1;
        int maxWidth       = -1;
        int maxHeight      = 0;
        int minHeight      = 0;
        int minWidth       = -1;
        float zIndex       = 0.0;
    };

    struct AnimationProperties {
        float animScaleX        = 1.2f;
        float animScaleY        = 1.2f;
        float duration          = 1.0f;
        bool isAnimatedElement  = false;
        float speed             = 0;
    };

    class CFRAME_API UIElement {

    public:
        UIElement(int x = 0, int y = 0, int w = -1, int h = -1, UIElement* parent = nullptr);
        virtual ~UIElement() = default;

        virtual void Render(Renderer& renderer) = 0;
        virtual void UpdateChildSizes() {}
        virtual void OnEvent(CFrameEvent& event);
        virtual ElementType GetElementType() const = 0;

        void UpdateVertices();
        void RotatePoint(Point& p, float angle, float cosA, float sinA, float cX, float cY);
        virtual void RegisterAnimator(std::shared_ptr<ApplicationManager> manager);

        void SetMargin(int marginleft, int marginRight, int marginTop, int marginBottom);
        void SetPadding(int padding);
        void SetParent(UIElement* p);
        void SetRadius(float topLeft = 0, float topRight = 0, float bottoLeft = 0, float bottomRight = 0);
        void SetHeight(int h);
        void SetWidth(int w);
        void SetX(int x);
        void SetY(int y);
        void SetAngle(float angle);
        void SetBorder(float border);
        void SetBorder(float t, float b, float r, float l);
        void SetBorderColor(Color color1, std::optional<Color> color2 = std::nullopt);
        void SetOpacity(float opacity);
        void SetMaxWidth(int maxWidth);
        void SetMinHeight(int minHeight);
        void SetMinWidth(int minHWidth);
        void SetZindex(float index);
        void SetPositionAbsolute(bool b);
        void SetBackgroundImage(std::string path);
        /// Sets the color of the UI element.
        /// @param color.
        /// The format is {r,g,b,a}. You can set a custom color using this format.
        void SetColor(Color color, std::optional<Color> color2 = std::nullopt);
        void SetScale(float scaleX, float scaleY);
        void SetVisibility(bool visibility);
        void SetDragToResize(bool b);
        void SetWidthResizable(bool is) { isWidthResizable = is; };
        void SetAnchorPoint(PositionMode mode);
        void SetOverflow(bool b);
        void SetIsDirty(bool b);
        void SetTextColor(Color color1, std::optional<Color> color2 = std::nullopt);
        void SetTextAlign(TextAlign alignX);

        void AnimateScale(float scaleX, float scaleY);
        void AnimateGradient(float speed);

        int    GetX()       const  { return x; }
        int    GetY()       const  { return y; }
        int    GetLocalX()  const  { return localX; }
        int    GetLocalY()  const  { return localY; }
        float  GetAngle()   const  { return properties.angle; }
        int    GetWidth()   const  { return width; }
        int    GetHeight()  const  { return height; }
        float  GetBorder()  const  { return properties.border; }

        bool  IsWidthResizable()        const  { return isWidthResizable; }
        bool  IsHeightResizable()       const  { return isHeightResizable; }
        bool  IsVisible()               const  { return isVisible; }
        bool  IsPositionAbsolute()      const  { return positionAbsolute; };
        bool  IsDraggable()             const  { return dragToResize; };
        bool  IsElementWithAnimation()  const  { return animProperties.isAnimatedElement; }
        bool  IsDirty()                 const  { return isDirty; }

        ElementProperties&    GetProperties()      { return properties; };
        AnimationProperties&  GetAnimProperties()  { return animProperties; };
        PositionMode GetAnchor() { return pMode; }

        void  SetOnHover(std::function<void()> onHover);
        void  SetOnLeave(std::function<void()> onLeave);

        int index;
        

    protected:
        UIElement* parent;  // Todo: dont use a raw pointer
        int x, y, width, height;
        int localX, localY;
        bool isWidthResizable;
        bool isHeightResizable;
        bool isVisible;
        bool isDirty = true;
        bool dragToResize;
        bool positionAbsolute = false;
        PositionMode pMode = PositionMode::TopLeft;
        std::unique_ptr<Texture> imageTexture;
        std::shared_ptr<ApplicationManager> applicationManager;
        
        ElementProperties properties;
        AnimationProperties animProperties;
        TextProperties textProps;
        OverFlowProperties overflow;
     
        std::function<void()> onHover = []() {};
        std::function<void()> onLeave = []() {};
    };

}
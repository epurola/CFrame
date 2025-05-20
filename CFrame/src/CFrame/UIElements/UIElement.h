#pragma once
#include <vector>
#include <cmath>
#include <optional>
#include "../Core.h"
#include "../Renderer/FontManager.h"
#include "../CFrameEvent/CFrameEvent.h"
#include "Color.h"
#include "../ApplicationManager.h"
#include "../Renderer/Renderer1.h"
#include "../Animator/Animator.h"

namespace CFrame 
{
    class Renderer1;
    class Animator;

    enum ElementType
    {
        CONTAINER,
        BUTTON,
        LABEL,
        INPUTFIELD,
        IMAGE
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

    struct TextProperties   {  
       std::vector<unsigned int> indices;
       std::vector<float> vertices; 

       float fontSize = 24;
       float offsetX  = 0.0f; 
       float offsetY  = 0.0f; 
       float opacity  = 1;

       int textHeight = 0;
       int textWidth = 0;
   
       Font font    = Font::Verdana;
       Color color1 = Color::White;
       Color color2 = Color::White;

       TextAlign textAlign = TextAlign::Center;
    };

    struct OverFlowProperties {
        bool overflow = false;
        int clipHeight;
        int clipWidth;
        int clipX;
        int clipY;
    };

    struct Vertices {
        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
    };

    struct LineProperties {
        Vertices vertices;
        Color color = Color::Blue;
        int height = 0;
        int width  = 0; 
    };

    struct Border {
        float left = 0.0f;
        float right = 0.0f;
        float top = 0.0f;
        float bottom = 0.0f;
    };

    struct Colors {
        glm::vec4 background1 = { 0.5f, 0.5f, 0.5f, 1.0f }; 
        glm::vec4 background2 = { 0.5f, 0.5f, 0.5f, 1.0f };
        glm::vec4 border1 = { 0.5f, 0.5f, 0.5f, 1.0f };
        glm::vec4 border2 = { 0.5f, 0.5f, 0.5f, 1.0f };
    };

    struct Margin {
        float left = 0.0f;
        float right = 0.0f;
        float top = 0.0f;
        float bottom = 0.0f;
    };

    struct ElementProperties 
    {
        Margin margin;
        int padding        = 0;

        Vertices vertices;

        Radius radius;
        Border border;
        Colors colors;

        float zIndex = 0.0;

        float scaleX       = 1;
        float scaleY       = 1;
        float angle        = 0.0f;
        float opacity      = 1;

        int maxWidth       = -1;
        int maxHeight      = 0;
        int minHeight      = 0;
        int minWidth       = -1;
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

        virtual void Render(Renderer1& renderer) = 0;
        virtual void Render(float timestep) = 0;
        virtual void UpdateChildSizes() {}
        virtual void OnEvent(CFrameEvent& event);
        virtual ElementType GetElementType() const = 0;
        virtual void SetScaleFactor(float scale);

        void UpdateVertices();
        void RotatePoint(Point& p, float angle, float cosA, float sinA, float cX, float cY);
        virtual void RegisterAnimator(std::shared_ptr<ApplicationManager> manager);

        void SetMargin(int marginleft, int marginRight, int marginTop, int marginBottom);
        void SetPadding(int padding);
        void SetParent(UIElement* p);
        void SetRadius(float topLeft = 0, float topRight = 0, float bottoLeft = 0, float bottomRight = 0);
        void SetHeight(float h);
        void SetWidth(float w);
        void SetX(float x);
        void SetY(float y);
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
        virtual void SetIsDirty(bool b);
        void SetTextColor(Color color1, std::optional<Color> color2 = std::nullopt);
        void SetTextAlign(TextAlign alignX);

        void SetAnimator(std::unique_ptr<Animator> anim);

        template <typename T, typename... Args>
        void StartAnimation(Args&&... args)
        {
            if (animator && animator->IsAnimating()) {
                // Current animation is still running, so ignore this new animation
                return;
            }
            static_assert(std::is_base_of<Animator, T>::value, "T must derive from Animator");
            animator = std::make_unique<T>(std::forward<Args>(args)..., *this);
            applicationManager->RegisterAnimation(*this);
        }

        void AnimateScale(float scaleX, float scaleY);
        void StopAnimation();
        void AnimateGradient(float speed);

        float  GetX()       const  { return x; }
        float  GetY()       const  { return y; }
        int    GetLocalX()  const  { return localX; }
        int    GetLocalY()  const  { return localY; }
        float  GetAngle()   const  { return properties.angle; }
        float  GetWidth()   const  { return width; }
        float  GetHeight()  const  { return height; }
        float  GetScaleFactor() const { return scaleFactor; }

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
        Border  GetBorder()  const { return properties.border; }

        void  SetOnHover(std::function<void()> onHover);
        void  SetOnLeave(std::function<void()> onLeave);

    protected:
        virtual bool MouseDragEvent(MouseDraggedEvent& event);
        virtual bool MousePressEvent(MouseButtonDownEvent& event); 
        virtual bool MouseReleaseEvent(MouseButtonReleasedEvent& event);  
        virtual bool MouseMoveEvent(MouseMovedEvent& event);             
       // virtual void MouseEnterEvent();                               
        virtual bool MouseLeaveEvent();                            
       // virtual void MouseDoubleClickEvent(MouseButtonDownEvent& event);
        

    protected:
        UIElement* parent;
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
        float scaleFactor = 1.0;
        int localX = 0;
        int localY = 0;
        bool isWidthResizable = true;
        bool isHeightResizable = true;
        bool isVisible = true;
        bool isDirty = true;
        bool dragToResize;
        bool positionAbsolute = false;

        PositionMode pMode = PositionMode::TopLeft;
        std::unique_ptr<Texture> imageTexture;
        std::shared_ptr<ApplicationManager> applicationManager;
        std::unique_ptr<Animator> animator;
        
        ElementProperties properties;
        AnimationProperties animProperties;
        TextProperties textProps;
        OverFlowProperties overflow;
     
        std::function<void()> onHover = []() {};
        std::function<void()> onLeave = []() {};
    };

}
#include "Button.h"
#include <cmath>
#include "../Renderer/FontLoader.h"


namespace CFrame 
{
	Button::Button(int x, int y, int w, int h, const std::string& text, 
          std::function<void()> onClick, UIElement* parent) 
		:UIElement(x, y, w, h, parent), onClick(onClick), text(text),
        animator(std::make_unique<Animator>(*this))
	{
        isWidthResizable = (w == -1);
        isHeightResizable = (h == -1);
		SetRadius(15,15,15,15);
        SetColor(Color::Gray);
 
	}

	Button::~Button()
	{

	}

	void Button::Render(Renderer& renderer)
	{
        //"C:/Users/eelip/MyGraphics/res/textures/white-queen.png"
        if (!labelTexture && GetElementType() == ElementType::BUTTON){
            labelTexture = std::make_unique<Texture>();
        }
        int renderWidth = width;
        int renderHeight = height;

        if (!animProperties.isAnimatedElement) {
             renderWidth = width * properties.scaleX;
             renderHeight = height * properties.scaleY;
        }
       
        if (animator->IsAnimating()) {
            animator->Update(0.016f); //60fps
        }

        int centeredX = x + (width - renderWidth) / 2;
        int centeredY = y + (height - renderHeight) / 2;
        
		renderer.DrawRectangle(centeredX, centeredY, renderWidth, renderHeight, 
            GetProperties(),
            animator->GetTime(), 
            animProperties.speed,
            labelTexture.get());
	}

    void Button::OnEvent(CFrameEvent& event)
    {
        // Early return if the event is not a MouseButtonDown event
        if (CFrameEventType::MouseButtonDown != event.GetEventType() &&
            event.GetEventType() != CFrameEventType::MouseMoved) {
            return;
        }

        if (event.GetEventType() == CFrameEventType::MouseButtonDown) {

            auto* mouseEvent = dynamic_cast<MouseButtonDownEvent*>(&event);
            if (!mouseEvent) {
                return; // Early return if the event is not a MouseButtonDownEvent
            }

            int xPos = mouseEvent->GetX();
            int yPos = mouseEvent->GetY();

            // Check if the mouse position is inside the button's bounds
            if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
                return; // Early return if the click is outside the button
            }

            //call the onClick handler
            CF_CORE_INFO("Button Clicked!");
            if (onClick) {
                onClick();
            }
            event.handled = true;
        }
        if (event.GetEventType() == CFrameEventType::MouseMoved) {

            auto* mouseEvent = dynamic_cast<MouseMovedEvent*>(&event);
            if (!mouseEvent) {
                return; // Early return if the event is not a MouseButtonDownEvent
            }

            int xPos = mouseEvent->GetX();
            int yPos = mouseEvent->GetY();

            // Check if the mouse position is inside the button's bounds
            if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
                if (hovering && !animator->IsAnimating()) { 
                    onLeave();
                    hovering = false;
                }
                
                return;
            }
            hovering = true;


            //call the onClick handler
            CF_CORE_INFO("Button Hovered!");
            if (onHover ) {
                onHover();
            }
            event.handled = true;
        }
    }

    void Button::SetOnClick(std::function<void()> onClick)
    {
        this->onClick = onClick;
    }

    void Button::StartAnimation()
    {
        animator->StartAnimation(animProperties.duration);
    }

}




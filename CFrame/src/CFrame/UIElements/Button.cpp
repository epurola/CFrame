#include "Button.h"
#include <cmath>

namespace CFrame 
{
	Button::Button(int x, int y, int w, int h, const std::string& text, 
          std::function<void()> onClick, UIElement* parent) 
		:UIElement(x, y, w, h, parent), onClick(onClick), text(text),
        animator(std::make_unique<Animator>(*this))
	{
        isWidthResizable = (w == -1);
        isHeightResizable = (h == -1);
		SetRadius(15);
        SetColor(Color::Gray);
	}

	Button::~Button()
	{

	}

	void Button::Render(Renderer& renderer)
	{
        int renderWidth = width;
        int renderHeight = height;

        if (!isAnimatedElement) {
             renderWidth = width * properties.scaleX;
             renderHeight = height * properties.scaleY;
        }
       
        animator->Update(0.016f); //60fps

        if (animator->IsAnimating()) {
            renderWidth = renderWidth * properties.animScaleX;
            renderHeight = renderHeight * properties.animScaleY;
        }
        int centeredX = x + (width - renderWidth) / 2;
        int centeredY = y + (height - renderHeight) / 2;
        
		renderer.DrawRectangle(centeredX, centeredY, renderWidth, renderHeight, 
            color.toSDLColor(255), 
            color2.toSDLColor(255), 
            0.0, 
            properties.radius, 
            animator->GetTime(), 
            animator->GetSpeed());
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

            if (IsElementWithAnimation()) {
                animator->StartAnimation(properties.duration);
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
                if (hovering) {
                    onLeave();
                    hovering = false;
                }
                
                return;
            }
            hovering = true;

            if (IsElementWithAnimation() && !animator->IsAnimating()) {
                animator->StartAnimation(properties.duration);
            }

            //call the onClick handler
            CF_CORE_INFO("Button Hovered!");
            if (onHover) {
                onHover();
            }
            event.handled = true;
        }
    }

    void Button::SetOnClick(std::function<void()> onClick)
    {
        this->onClick = onClick;
    }

    void Button::AnimateGradient(float speed)
    {
        animator->SetSpeed(speed);
    }
	
}




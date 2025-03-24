#include "Button.h"
#include <cmath>

namespace CFrame 
{
	Button::Button(int x, int y, int w, int h, const std::string& text, 
		           std::function<void()> onClick, UIElement* parent)
		:UIElement(x, y, w, h, parent), onClick(onClick), text(text)
	{
		isWidthResizable = false;
		isHeightResizable = false;
		SetRadius(15);
	}

	Button::~Button()
	{

	}

	void Button::Render(Renderer& renderer)
	{
		renderer.DrawRectangle(x, y, width, height, color.toSDLColor(255), 0.0, properties.radius, properties.scale);
	}

    void Button::OnEvent(CFrameEvent& event)
    {
        // Early return if the event is not a MouseButtonDown event
        if (CFrameEventType::MouseButtonDown != event.GetEventType()) {
            return;
        }

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
	
}




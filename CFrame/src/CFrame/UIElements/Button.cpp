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
		renderer.DrawRectangle(x, y, width, height, { 0,255,255,255 }, 0.0, properties.radius);
	}

	void Button::OnEvent(CFrameEvent& event)
	{
		if (CFrameEventType::MouseButtonDown == event.GetEventType()) {
			if (auto* mouseEvent = dynamic_cast<MouseButtonDownEvent*>(&event)) {
				int xPos = mouseEvent->GetX();
				int yPos = mouseEvent->GetY();
				
				if (xPos >= x && xPos <= (x + width) && (yPos >= y && yPos <= (y + height)))
				{
					CF_CORE_INFO("Button Clicked!");
					event.handled = true;
				}
				
			}
		}
	}
	
}




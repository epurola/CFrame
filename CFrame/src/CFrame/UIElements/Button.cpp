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
				
				if ((xPos >= x + 50 && xPos <= (x + width -50)) && (yPos >= y && yPos <= (y + height)))
				{
					CF_CORE_INFO("Button Clicked!");
					event.handled = true;
				}
				int circleX = xPos - (x + width / 2);  // Center of button adjusted by width/2
				int circleY = yPos - (y + height / 2); // Center of button adjusted by height/2

				// Lambda function to check if the mouse click is inside a circle of radius 50
				auto in = [](int x, int y) {
					return std::sqrt(x * x + y * y) < 50.0f;  // Use sqrt to check distance from the center
					};

				// Check if the click is inside the circle
				if (in(circleX, circleY)) {
					CF_CORE_INFO("Button Clicked!");
					event.handled = true;
				}
			}
		}
	}
	
}




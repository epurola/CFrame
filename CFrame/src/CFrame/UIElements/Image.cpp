#include "Image.h"
#include "../RenderAPI/Renderer2D.h"

namespace CFrame 
{
	Image::Image(int x, int y, int w, int h, std::string path, UIElement* parent)
		:UIElement(x,y,w,h,parent)
	{
		imageTexture = std::make_unique<Texture>(path);
	}

	Image::~Image()
	{

	}

	void Image::Render(Renderer1& renderer)
	{
		renderer.DrawRectangle(
			GetX(),
			GetY(),
			GetWidth(),
			GetHeight(),
			GetProperties(),
			0.0,
			1.0f,
			imageTexture.get());
	}

	void Image::Render()
	{
		QuadInstance instance{};

		// Position and size (example values — should be based on your layout system)
		instance.position = { x, y };         // Replace with actual position
		instance.size = { width, height }; // Replace with actual size

		// Base colors (RGBA)
		instance.color1 = { properties.color1.r,properties.color1.g,properties.color1.b , properties.opacity }; // White base
		instance.color2 = { properties.color2.r,properties.color2.g,properties.color2.b , properties.opacity }; // Slight gradient

		// Border colors (optional)
		instance.borderColor1 = { properties.borderColor1.r,properties.borderColor1.g,properties.borderColor1.b , properties.opacity }; // Black
		instance.borderColor2 = { properties.borderColor2.r,properties.borderColor2.g,properties.borderColor2.b , properties.opacity };

		// Border sizes (top, right, bottom, left)
		instance.borderSizes = { properties.borderTop, properties.borderRight, properties.borderBottom, properties.borderLeft };

		// Radius for corners
		instance.radius = { properties.radius.topLeft, properties.radius.topRight, properties.radius.bottomLeft, properties.radius.bottomRight };

		// Animation parameters
		instance.time = 0.0f;  //  pass actual elapsed time
		instance.speed = 0.0f;
		instance.angle = 0.0f;


		// Submit to renderer
		Renderer2D::DrawQuad(instance);
	}

	void Image::OnEvent(CFrameEvent& event)
	{
		switch (event.GetEventType()) 
		{
			case CFrameEventType::MouseButtonDown:
			{
				auto& mouseEvent = static_cast<MouseButtonDownEvent&>(event);
				if (mouseEvent.GetX() >= x && mouseEvent.GetX() <= x + width &&
					mouseEvent.GetY() >= y && mouseEvent.GetY() <= y + height)
				event.handled = MousePressEvent(mouseEvent);
				return;
			}

			case CFrameEventType::MouseMoved:
			{
				auto& mouseEvent = static_cast<MouseMovedEvent&>(event);
				if (mouseEvent.GetX() >= x && mouseEvent.GetX() <= x + width &&
					mouseEvent.GetY() >= y && mouseEvent.GetY() <= y + height)
				event.handled = MouseMoveEvent(mouseEvent); 
				return;
			}

			case CFrameEventType::MouseDragged:
			{
				auto& mouseEvent = static_cast<MouseDraggedEvent&>(event);
				event.handled = MouseDragEvent(mouseEvent);
				return;
			}

			case CFrameEventType::MouseButtonReleased:
			{
				auto& mouseEvent = static_cast<MouseButtonReleasedEvent&>(event);
				if (mouseEvent.GetX() >= x && mouseEvent.GetX() <= x + width &&
					mouseEvent.GetY() >= y && mouseEvent.GetY() <= y + height)
				event.handled = MouseReleaseEvent(mouseEvent);
				return;
			}
		}
	}

	void Image::SetOnEvent(std::function<void()> onEvent)
	{
		this->onEvent = onEvent;
	}

}


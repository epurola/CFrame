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
		QuadInstanceT instancet{};

		instancet.position = { x, y };
		instancet.size = { width , height };

		// Base colors (RGBA)
		instancet.color1 = { properties.color1.r / 255.0f,properties.color1.g / 255.0f,properties.color1.b / 255.0f , properties.opacity };
		instancet.color2 = { properties.color2.r / 255.0f,properties.color2.g / 255.0f,properties.color2.b / 255.0f , properties.opacity };

		// Border colors 
		instancet.borderColor1 = { properties.borderColor1.r / 255.0f,properties.borderColor1.g / 255.0f,properties.borderColor1.b / 255.0f , properties.opacity };
		instancet.borderColor2 = { properties.borderColor2.r / 255.0f,properties.borderColor2.g / 255.0f,properties.borderColor2.b / 255.0f, properties.opacity };

		// Border sizes (top, right, bottom, left)
		instancet.borderSizes = { properties.borderTop, properties.borderRight, properties.borderBottom, properties.borderLeft };

		// Radius for corners
		instancet.radius = { properties.radius.topLeft, properties.radius.topRight, properties.radius.bottomLeft, properties.radius.bottomRight };

		// Animation parameters
		instancet.time = 0.0f;  //  pass actual elapsed time
		instancet.speed = 0.0f;
		instancet.angle = 0.0f;
		instancet.texture = imageTexture.get();
		instancet.p = GetProperties();
		Renderer2D::DrawTextured(instancet);
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


#include "Image.h"

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

	void Image::Render(Renderer& renderer)
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

	void Image::OnEvent(CFrameEvent& event)
	{
		switch (event.GetEventType()) 
		{
			case CFrameEventType::MouseDragged: 
			{
				auto& dragEvent = static_cast<MouseDraggedEvent&>(event);
				MouseDragEvent(dragEvent);
			}
		}
	}

	void Image::SetOnEvent(std::function<void()> onEvent)
	{
		this->onEvent = onEvent;
	}
}


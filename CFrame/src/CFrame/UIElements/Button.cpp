#include "Button.h"

namespace CFrame 
{
	Button::Button(int x, int y, int w, int h, const std::string& text, 
		           std::function<void()> onClick, UIElement* parent)
		:UIElement(x, y, w, h, parent), onClick(onClick), text(text)
	{
	
	}
	Button::~Button()
	{

	}
	void Button::Render(Renderer& renderer)
	{
		renderer.DrawRectangle(x, y, width, height, { 0,255,255,255 }, 0.0, 0);
	}
	void Button::OnEvent(CFrameEvent& event)
	{
		CF_CORE_INFO("Button was pressed");
	}
}


#include "Label.h"

namespace CFrame 
{
	Label::Label(int x, int y, int w, int h, const std::string& text, UIElement* parent)
		:UIElement(x,y,w,h,nullptr)
	{
		CreateTexture(text, w, h);
	}

	Label::~Label()
	{

	}
	void Label::Render(Renderer& renderer)
	{
		if (sdfTexture == nullptr) {
			sdfTexture = new Texture(textTexture, width, height);
		}
	}

	void Label::CreateTexture(const std::string& text, int w, int h)
	{
		
	}
	void Label::OnEvent(CFrameEvent& event)
	{
	}
}


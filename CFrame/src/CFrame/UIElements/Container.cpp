#include "Container.h"

namespace CFrame 
{
	Container::Container(int x, int y, int w, int h, UIElement* parent)
		:UIElement(x, y, w, h, parent), 
		 xAlign(AlignItems::Start), yAlign(AlignItems::Start)
	{

	}

	Container::~Container()
	{
		for (auto& child : children) 
		{
			delete child;
		}
	}
	void Container::SetSpacing(int spacing)
	{
		this->spacing = spacing;
	}

	void Container::AddChild(UIElement* child)
    {
		children.push_back(child);
		child->SetParent(this);
		UpdateChildSizes();
    }

	void Container::Render(Renderer& renderer)
	{

	}

	void Container::SetAlignment(AlignItems xAlign, AlignItems yAlign)
	{
		this->xAlign = xAlign;
		this->yAlign = yAlign;
	}
}


#include "Container.h"

namespace CFrame 
{
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
    }

	void Container::Render()
	{

	}

	void Container::SetAlignment(AlignItems xAlign, AlignItems yAlign)
	{
		this->xAlign = xAlign;
		this->yAlign = yAlign;
	}
}


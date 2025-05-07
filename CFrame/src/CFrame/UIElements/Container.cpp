#include "Container.h"

namespace CFrame 
{
	Container::Container(int x, int y, int w, int h, UIElement* parent)
		:UIElement(x, y, w, h, parent), 
		 xAlign(AlignItems::Start), yAlign(AlignItems::Start) ,scrollEnabled(false), spacing(0)
	{
		
	}

	Container::~Container()
	{
		for (auto& child : children)
			if (child) 
			{
				delete child;
			}
	}

	void Container::AddChild(UIElement* child)
    {
		children.push_back(child);
		renderChildren.push_back(child);
		child->SetParent(this);
	//	UpdateChildSizes();
    }

	void Container::Render(Renderer& renderer)
	{
		if (!IsVisible()) return;
	
		renderer.DrawRectangle((float)x, (float)y, (float)width, (float)height,
				GetProperties(), 1.0f, 1.0f, nullptr);
		
		for (auto& child : renderChildren) 
		{
			if (child->IsVisible()) 
			{
				child->Render(renderer);
			}
		}
	}

	void Container::OnEvent(CFrameEvent& event)
	{
		if (!IsVisible()) return;

		for (auto& child : children) 
		{
			if (event.handled)  return; 
			child->OnEvent(event);
		}

		switch (event.GetEventType()) 
		{
			case CFrameEventType::MouseDragged:
			{
				auto& mouseEvent = static_cast<MouseDraggedEvent&>(event);
				event.handled = HandleMouseDrag(mouseEvent);
				return;
			}
				
			case CFrameEventType::MouseScroll: 
			{
				auto& mouseEvent = static_cast<MouseScrolledEvent&>(event);
				event.handled = HandleMouseScroll(mouseEvent);
				return;
			}
		}
		return;
	}

	void Container::ToFront(UIElement* child)
	{
		auto it = std::find(renderChildren.begin(), renderChildren.end(), child);
		if (it == renderChildren.end()) return;
		UIElement* target = *it;
		renderChildren.erase(it);
		renderChildren.push_back(target);
	}

	void Container::ToBack(UIElement* child)
	{

	}

	bool Container::HandleMouseDrag(MouseDraggedEvent& e)
	{
		if (!(e.GetStartX() > x + (width - 15) && e.GetStartX() < x + width)) return false;

		if (!dragToResize) return false;
			
		SetWidth((width + (int)(e.GetCurrentX() - e.GetStartX())));
		UpdateChildSizes();
		parent->UpdateChildSizes();
		//toDo: use a different flag so the container does not divide equally
		return true;
	}

	bool Container::HandleMouseScroll(MouseScrolledEvent& e)
	{
		if (!(e.GetMouseX() >= x && e.GetMouseX() <= x + width) &&
			(e.GetMouseY() >= y && e.GetMouseY() <= y + height))  return false;

		if (!scrollEnabled) return false;

		for (auto& child : children) 
		{
			int newY = child->GetY() + (e.GetDistanceY() * 10); //ToDo: Add variable to cotrol the sensitivity of scroll
			child->SetY(newY);
			child->UpdateChildSizes();
			child->UpdateVertices();
		}
		return true;	
	}

	void Container::SetIsDirty(bool b)
	{
		// Deprecated
		isDirty = b;

		if (b) {
			for (auto& child : children)
			{
				child->SetIsDirty(b);
			}
		}
	}

	void Container::SetAlignment(AlignItems xAlign, AlignItems yAlign)
	{
		this->xAlign = xAlign;
		this->yAlign = yAlign;
	}

	void Container::SetScrollEnabled(bool b)
	{
		scrollEnabled = b;
	}

	void Container::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
	{
		applicationManager = manager;
		for (auto child : children)
		{
			child->RegisterAnimator(manager);
		}
	}

	void Container::SetSpacing(int spacing)
	{
		this->spacing = spacing;
	}
}


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
			delete child;
	}

	void Container::SetSpacing(int spacing)
	{
		this->spacing = spacing;
	}

	void Container::AddChild(UIElement* child)
    {
		children.push_back(child);
		renderChildren.push_back(child);
		child->SetParent(this);
		child->index = static_cast<int>(children.size()) - 1;
		UpdateChildSizes();
    }

	void Container::Render(Renderer& renderer)
	{
		if (!IsVisible()) return;

		renderer.DrawRectangle(x, y, width, height,
			GetProperties(), 1.0f, 1.0f, nullptr);

		for (auto& child : renderChildren) {
			child->Render(renderer);
		}
	}

	void Container::SetAlignment(AlignItems xAlign, AlignItems yAlign)
	{
		this->xAlign = xAlign;
		this->yAlign = yAlign;
	}

	void Container::OnEvent(CFrameEvent& event)
	{
		if (!IsVisible()) return;

		for (auto& child : children) {
			if (event.handled)  return;
			child->OnEvent(event);
		}
	
		if (event.GetEventType() == CFrameEventType::MouseDragged) {
			auto* mouseEvent = dynamic_cast<MouseDraggedEvent*>(&event);
			if (mouseEvent->GetStartX() > x + (width - 15) && mouseEvent->GetStartX() < x + width) {
				if (dragToResize) {
					SetWidth(width + (mouseEvent->GetCurrentX() - mouseEvent->GetStartX()));
					event.handled = true;
					//toDo: use a different flag so the container does not divide equally
					CF_CORE_INFO("RESIZE! {0}", width + (mouseEvent->GetCurrentX() - mouseEvent->GetStartX()));
				}
			}
		}
		

	}
	void Container::ToFront(UIElement* child)
	{
		auto it = std::find(renderChildren.begin(), renderChildren.end(), child);

		if (it == renderChildren.end())
			return;

		UIElement* target = *it;
		renderChildren.erase(it);
		renderChildren.push_back(target);
	}

	void Container::ToBack(UIElement* child)
	{

	}
}


#include "Container.h"
#include "../RenderAPI/Renderer2D.h"

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

	void Container::Render(Renderer1& renderer)
	{
		if (!IsVisible()) return;
	
		
		renderer.DrawRectangle(x, y, (float)width, (float)height,
				GetProperties(), 1.0f, 1.0f, imageTexture.get());
		
	
		for (auto& child : renderChildren) 
		{
			if (child->IsVisible()) 
			{
				child->Render(renderer);
			}
		}
	}

	void Container::Render(float timestep)
	{
		static float accumulatedTime = 0.0f;
		accumulatedTime += timestep;

		QuadInstance instance{};

		instance.position = { x, y };
		instance.size = { width * properties.scaleX, height * properties.scaleY };

		// Base colors (RGBA)
		properties.colors.background1.a = properties.opacity;
		properties.colors.background2.a = properties.opacity;
		instance.color1 = properties.colors.background1;
		instance.color2 = properties.colors.background2;

		// Border colors 
		instance.borderColor1 = properties.colors.border1;
		instance.borderColor2 = properties.colors.border2;

		instance.borderSizes = { properties.border.top, properties.border.right, properties.border.bottom, properties.border.left };

		// Radius for corners
		instance.radius = { properties.radius.topLeft, properties.radius.topRight, properties.radius.bottomLeft, properties.radius.bottomRight };

		// Animation parameters
		instance.time = accumulatedTime;  //  pass actual elapsed time
		instance.speed = 0.0f;
		instance.angle = 0.0f;

		if (!imageTexture) 
		{
			Renderer2D::DrawQuad(instance);
		}
        else 
		{
			QuadInstanceT instancet{};

			instancet.position = { x, y };
			instancet.size = { width , height  };

			// Base colors (RGBA)
			instance.color1 = properties.colors.background1;
			instance.color2 = properties.colors.background2;

			// Border colors 
			instance.borderColor1 = properties.colors.border1;
			instance.borderColor2 = properties.colors.border2;

			instance.borderSizes = { properties.border.top, properties.border.right, properties.border.bottom, properties.border.left };

			// Radius for corners
			instancet.radius = { properties.radius.topLeft, properties.radius.topRight, properties.radius.bottomLeft, properties.radius.bottomRight };

			// Animation parameters
			instancet.time = 1.0f;  
			instancet.speed = 1.0f;
			instancet.angle = 0.0f;
			instancet.texture = imageTexture.get();
			instancet.p = GetProperties();

			Renderer2D::DrawTextured(instancet);
		}
		
		for (auto& child : renderChildren)
		{
			if (child->IsVisible())
			{
				child->Render(timestep);
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
			case CFrameEventType::MouseButtonDown:
			{
				auto& mouseEvent = static_cast<MouseButtonDownEvent&>(event);
				if (mouseEvent.GetX() >= x && mouseEvent.GetX() <= x + width &&
					mouseEvent.GetY() >= y && mouseEvent.GetY() <= y + height)
				event.handled = MousePressEvent(mouseEvent);
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

			case CFrameEventType::MouseMoved:
			{
				auto& mouseEvent = static_cast<MouseMovedEvent&>(event);
				if (mouseEvent.GetX() >= x && mouseEvent.GetX() <= x + width &&
					mouseEvent.GetY() >= y && mouseEvent.GetY() <= y + height)
				event.handled = MouseMoveEvent(mouseEvent);
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

	void Container::SetScaleFactor(float scale) 
	{
		scaleFactor = scale;
		x = x * scale;
		y = y * scale;
		width = width * scale;
		height = height * scale;
		textProps.fontSize = static_cast<int>(textProps.fontSize * scale);

		// Also scale margins and paddings
		

		spacing *= scale;
		properties.padding *= scale;

		for (auto& child : children) 
		{
			child->SetScaleFactor(scale);	
		}
	}

}


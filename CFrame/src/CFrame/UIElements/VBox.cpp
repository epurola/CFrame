#include "VBox.h"

namespace CFrame 
{

    VBox::VBox(int x, int y, int w, int h, UIElement* parent)
        : Container(x, y, w, h, nullptr)
    {
        isHeightResizable = (h == -1); 
        isWidthResizable = (w == -1);
        dragToResize = false;
    }

    VBox::~VBox()
	{
		
	}

    void VBox::Render(Renderer& renderer)
    {
        renderer.DrawRectangle(x, y, width, height, 
            properties.color1.toSDLColor(255), 
            properties.color1.toSDLColor(255), 
            0.0, 
            properties.radius, 1.0f, 1.0f,0.0, 
            properties.color1.toSDLColor(255),
            properties.color1.toSDLColor(255));

        for (auto& child : children) {
            child->Render(renderer);
        }
    }

    void VBox::OnEvent(CFrameEvent& event)
    {
        for (auto& child : children) {
            if (event.handled)  return; 

            child->OnEvent(event);
        }
        if (event.GetEventType() == CFrameEventType::MouseDragged ) {
            auto* mouseEvent = dynamic_cast<MouseDraggedEvent*>(&event);
            if (mouseEvent->GetStartX() > x + (width - 10) && mouseEvent->GetStartX() < x + width) {
                CF_CORE_INFO("RESIZE! {0}" , width);
                if (dragToResize) {
                    SetWidth(width + (mouseEvent->GetCurrentX() - mouseEvent->GetStartX()));
                    //toDo: use a different flag so the container does not divide equally
                }
            }
        }
    }

    void VBox::UpdateChildSizes()
	{
        if (children.empty())
            return;

        int fixedHeight = 0;
        int flexibleCount = 0;
        int maxChildWidth = 0;
        int flexibleHeight = 0;
        int totalMargins = 0;

        int xpos = GetX() + properties.padding + properties.marginLeft; // add margin
        int ypos = GetY() + properties.padding + properties.marginTop;

        for (auto* child : children)
        {
            if (child->IsHeightResizable())
            {
                flexibleCount++;
            }
            else
            {
                fixedHeight += child->GetHeight() + (child->GetProperties().marginTop + child->GetProperties().marginBottom);
            }
            if (child->GetWidth() > maxChildWidth && !child->IsWidthResizable())
            {
                maxChildWidth = child->GetWidth();
            }
            totalMargins += child->GetProperties().marginLeft + child->GetProperties().marginRight;
        }

        int totalSpacing = spacing * (children.size() - 1);
        int availableSpace = height - fixedHeight - totalSpacing - totalMargins - (properties.padding * 2);

        if (flexibleCount > 0)
        {
            flexibleHeight = (availableSpace / flexibleCount);
        }
        else
        {
            flexibleHeight = 0;
        }

        if (maxChildWidth == 0) {
            maxChildWidth = height - (properties.padding * 2);
        }


        switch (yAlign)
        {
        case AlignItems::Center:
            ypos = y + (height / 2) - (fixedHeight + totalSpacing + (flexibleHeight * flexibleCount)) / 2;
            break;
        case AlignItems::End:
            ypos = y + height - (fixedHeight + totalSpacing + (flexibleHeight * flexibleCount));
            break;
        case AlignItems::Start:
            ypos = ypos;
            break;
        default:
            ypos;
        }

        switch (xAlign)
        {
        case AlignItems::Center:
            xpos = x + (width - maxChildWidth) / 2;
            break;
        case AlignItems::End:
            xpos = x + width - maxChildWidth;
            break;
        case AlignItems::Start:
            break;
        case AlignItems::Stretch:
            xpos = xpos;
            break;
        default:
            xpos;
        }

        for (size_t i = 0; i < children.size(); i++)
        {
            UIElement* child = children[i];

           
            xpos = xpos + child->GetProperties().marginLeft;
            ypos = ypos + child->GetProperties().marginTop;
            
            child->SetX(xpos);
            child->SetY(ypos);
            
            if (child->GetElementType() == ElementType::CONTAINER && child->IsHeightResizable())
            {
                child->SetWidth(width - (properties.padding * 2));
                child->SetHeight(flexibleHeight);
                child->SetX(xpos);
                child->SetY(ypos);
                child->UpdateChildSizes();
            }

            if (child->GetElementType() == ElementType::CONTAINER && !child->IsHeightResizable())
            {
                child->SetX(xpos);
                child->SetY(ypos);
                child->UpdateChildSizes();
            }

            if (child->IsHeightResizable())
            {
                child->SetHeight(flexibleHeight);
            }

            if (xAlign == AlignItems::Stretch)
            {
                child->SetWidth(width - (properties.padding * 2));
            }

            if (child->IsWidthResizable())
            {
                child->SetWidth(width - (properties.padding * 2) - (child->GetProperties().marginRight + child->GetProperties().marginLeft));

                if (child->GetElementType() == ElementType::CONTAINER)
                {
                    child->UpdateChildSizes();
                }
                if (xAlign == AlignItems::Center) {
                    child->SetWidth(width - xpos);
                }
            }

            ypos += child->GetHeight() + child->GetProperties().marginBottom;
            xpos -= child->GetProperties().marginLeft; //Reset so the next element is                                        
            if (i < children.size() - 1)                //relative to the container not the element before it
            {
                ypos += spacing ;
            }
        }
	}
   
}


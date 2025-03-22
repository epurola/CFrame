#include "VBox.h"

namespace CFrame 
{
    VBox::VBox(int w, int h)
        :Container(0,0,w,h, nullptr)
	{
        isHeightResizable = true;
        isWidthResizable = true;
	}

	VBox::~VBox()
	{
		
	}

    void VBox::Render(Renderer& renderer)
    {
        renderer.DrawRectangle(x, y, width, height, { 255,255,200,255 }, 0.0, 0);
        for (auto& child : children) {
            child->Render(renderer);
        }
    }

    void VBox::OnEvent(CFrameEvent& event)
    {
        if (CFrameEventType::WindowResized == event.GetEventType()) {
           
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

        int xpos = GetX() + properties.padding; // add margin
        int ypos = y + properties.padding;

        for (auto* child : children)
        {
            if (child->IsHeightResizable())
            {
                flexibleCount++;
            }
            else
            {
                fixedHeight += child->GetHeight() + (child->GetProperties().marginTop * 2);
            }
            if (child->GetWidth() > maxChildWidth && !child->IsWidthResizable())
            {
                maxChildWidth = child->GetWidth();
            }
            totalMargins += child->GetProperties().marginLeft * 2;
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

            child->SetX(xpos + child->GetProperties().marginLeft);
            child->SetY(ypos + child->GetProperties().marginTop);
            

            if (dynamic_cast<Container*>(child) && child->IsHeightResizable())
            {
                child->SetWidth(width - (properties.padding * 2));
                child->SetHeight(flexibleHeight);
                child->SetX(xpos);
                child->SetY(ypos);
                child->UpdateChildSizes();
            }

            if (dynamic_cast<Container*>(child) && !child->IsHeightResizable())
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
                child->SetWidth(width - (properties.padding * 2));


                if (xAlign == AlignItems::Center) {
                    child->SetWidth(width - xpos);
                }
            }

            ypos += child->GetHeight();
            if (i < children.size() - 1)
            {
                ypos += spacing;
            }
        }
	}
   
}


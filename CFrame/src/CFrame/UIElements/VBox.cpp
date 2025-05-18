#include "VBox.h"

namespace CFrame 
{

    VBox::VBox(int x, int y, int w, int h, UIElement* parent)
        : Container(x, y, w, h, parent)
    {
        isHeightResizable = (h == -1); 
        isWidthResizable = (w == -1);
        dragToResize = false;
    }

    VBox::~VBox()
	{
		
	}
  
    void VBox::UpdateChildSizes()
    {
        if (children.empty()) return;

        ResetLayoutMetrics();

        int xpos = GetX() + properties.padding + properties.margin.left; 
        int ypos = GetY() + properties.padding + properties.margin.top;

        PrecalculateLayoutMetrics();
  
        UpdateAlignment(xpos, ypos);

        for (size_t i = 0; i < children.size(); i++)
        {
            UIElement* child = children[i];
            if (!child->IsVisible()) continue;

            ElementProperties p = child->GetProperties();
            
            xpos = xpos + p.margin.left;
            ypos = ypos + p.margin.top;

            if (child->IsPositionAbsolute()) {
                HandleAbsolutePosition(*child);
                continue;
            }

            child->SetX(xpos);
            child->SetY(ypos);
            
            //Make container fill the width
            if (child->GetElementType() == ElementType::CONTAINER && child->IsHeightResizable())
            {
                child->SetWidth(width - (properties.padding * 2));
                child->SetHeight(flexibleHeight);
            }

            if (child->IsHeightResizable())
            {
                child->SetHeight(flexibleHeight);
            }

            if (child->IsWidthResizable())
            {
                child->SetWidth(width - (properties.padding * 2) - (p.margin.right + p.margin.left));

                if (xAlign == AlignItems::Center) 
                {
                    child->SetWidth(width - xpos);
                }
            }

            if (xAlign == AlignItems::Stretch)
            {
                child->SetWidth(width - (properties.padding * 2));
            }

            ypos += child->GetHeight() + p.margin.bottom;
            xpos -= p.margin.left; //Reset so the next element is 
                                  //relative to the container not the element before it
            if (i < children.size() - 1)       
            {
                ypos += spacing ;
            }

            child->UpdateChildSizes();
            child->UpdateVertices();
        }
	}

    void VBox::UpdateAlignment(int& xpos, int& ypos)
    {
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
    }

    void VBox::ResetLayoutMetrics()
    {
        fixedHeight    = 0;
        flexibleCount  = 0;
        maxChildWidth  = 0;
        flexibleHeight = 0;
        totalMargins   = 0;
    }

    void VBox::PrecalculateLayoutMetrics()
    {
        for (auto* child : children)
        {
            ElementProperties p = child->GetProperties();

            if (!child->IsVisible() || child->IsPositionAbsolute()) continue;

            if (child->IsHeightResizable())
            {
                flexibleCount++;
            }
            else
            {
                fixedHeight += child->GetHeight() + (p.margin.top + p.margin.bottom);
            }

            if (child->GetWidth() > maxChildWidth && !child->IsWidthResizable())
            {
                maxChildWidth = child->GetWidth();
            }

            totalMargins += p.margin.left + p.margin.right;
        }

        totalSpacing = static_cast<int>(spacing * (children.size() - 1));
        availableSpace = height - fixedHeight - totalSpacing - totalMargins - (properties.padding * 2);
        flexibleHeight = (flexibleCount > 0) ? (availableSpace / flexibleCount) : 0;

        if (maxChildWidth == 0) 
        {
            maxChildWidth = width - (properties.padding * 2);
        }
    }

    void VBox::HandleAbsolutePosition(UIElement& child)
    {
        if (child.IsWidthResizable()) 
        {
            child.SetWidth(width - (properties.padding * 2) - (GetX() + child.GetLocalX()));
        }

        if (child.GetAnchor() == PositionMode::BottomLeft) {
            child.SetX(GetX() + child.GetLocalX());
            child.SetY(GetY() + GetHeight() - child.GetHeight() - child.GetProperties().margin.bottom - child.GetLocalY());
        }
        else 
        {
            child.SetX(GetX() + child.GetLocalX());
            child.SetY(GetY() + child.GetLocalY());
        }
        child.UpdateChildSizes();
        child.UpdateVertices();//Update the drawing info of the child
    }
}


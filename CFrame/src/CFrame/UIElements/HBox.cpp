#include "HBox.h"
namespace CFrame {

	HBox::HBox(int x, int y, int w, int h, UIElement* parent)
		:Container(x,y,w,h, parent)
	{
		isHeightResizable = (h == -1); 
		isWidthResizable = (w == -1);
        SetColor(Color::LightGray);
	}

	HBox::~HBox()
	{

	}

    //ToDo: Refactor this...
	void HBox::UpdateChildSizes()
	{
        if (children.empty())return;

        ResetLayoutMetrics();
         //todo: Add margin here?
        int xpos = x + properties.padding;
        int ypos = y + properties.padding;

        PrecalculateLayoutMetrics();

        switch (xAlign)
        {
             case AlignItems::Center:
                 xpos = x + (width / 2) - (fixedWidth + totalSpacing + (flexWidth * flexibleCount)) / 2;
                 break;

             case AlignItems::End:
                 xpos = x + width - (fixedWidth + totalSpacing + properties.padding + (flexWidth * flexibleCount));
                 break;

             case AlignItems::Start:
                 xpos = x + properties.padding;
                 break;

             default:
                 xpos = xpos;
                 break;
        }


        // Assign positions to each child
        for (size_t i = 0; i < children.size(); i++)
        {
            UIElement* child = children[i];

            if (!child->IsVisible()) continue;

            if (child->IsPositionAbsolute()) {
                HandleAbsolutePosition(*child);
                continue;
            }
            
            ElementProperties p = child->GetProperties();

            switch (yAlign)
            {
                 case AlignItems::Center:
                     ypos = y + (height / 2) - (child->GetHeight() / 2);
                     break;
                 case AlignItems::End:
                     ypos = y + (height - maxChildHeight) - properties.padding;
                     break;
                 case AlignItems::Start:
                     ypos = y + properties.padding;
                     break;
                 case AlignItems::Stretch:
                     ypos = y + properties.padding;
                     break;
                 default:
                     ypos = y + properties.padding;
                     break;
            }

            xpos = xpos + p.margin.left; 
            ypos = ypos + p.margin.top;
  
            child->SetX(xpos);
            child->SetY(ypos);
            
            if (child->GetElementType() == ElementType::CONTAINER && child->IsWidthResizable())
            {
                if (flexWidth > p.maxWidth && p.maxWidth > 0) {
                    flexWidth = p.maxWidth;
                }
                child->SetWidth(flexWidth);
                child->SetHeight(height - (properties.padding * 2));
            }

            if (child->IsWidthResizable())
            {
                child->SetWidth(flexWidth);
            }

            if (yAlign == AlignItems::Stretch)
            {
                child->SetHeight(height - (properties.padding * 2));
            }

            if (child->IsHeightResizable() || child->GetHeight() < 0)
            {
                child->SetHeight(height - (properties.padding * 2));
                child->SetX(xpos + p.margin.left);
                child->SetY(ypos + p.margin.top);
            }

            xpos += child->GetWidth() + p.margin.right;

            if (i < children.size() - 1)
            {
                xpos += spacing;
            }

            child->UpdateVertices();
            child->UpdateChildSizes();
        }
	}

    void HBox::ResetLayoutMetrics()
    {
        fixedWidth     = 0;
        flexWidth      = 0;
        flexibleCount  = 0;
        maxChildHeight = 0;
        totalMargins   = 0;
    }

    void HBox::PrecalculateLayoutMetrics()
    {
        for (auto* child : children)
        {
            if (!child->IsVisible() || child->IsPositionAbsolute())
            {
                continue;
            }

            if (child->IsWidthResizable())
            {
                flexibleCount++;
                totalMargins += child->GetProperties().margin.left + child->GetProperties().margin.right;
            }
            else
            {
                fixedWidth += child->GetWidth() + (child->GetProperties().margin.left + child->GetProperties().margin.right);//May not be right
            }
            if (child->GetHeight() > maxChildHeight && !child->IsHeightResizable())
            {
                maxChildHeight = child->GetHeight();
            }
        }

        totalSpacing = static_cast<int>(spacing * (children.size() - 1));
        availableSpace = width - fixedWidth - totalSpacing - totalMargins - (properties.padding * 2);
        flexWidth = (flexibleCount > 0) ? (availableSpace / flexibleCount) : 0;

        if (maxChildHeight == 0) 
        {
            maxChildHeight = height - (properties.padding * 2);
        }
    }

    void HBox::HandleAbsolutePosition(UIElement& child)
    {
        if (child.IsWidthResizable()) 
        {
            child.SetWidth(width - child.GetLocalX() - properties.padding * 2 - child.GetProperties().margin.right);
        }

        if (child.GetAnchor() == PositionMode::BottomLeft) 
        {
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


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
            if (!child->IsVisible() || child->IsPositionAbsolute()) {
                continue;
            }
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

        int totalSpacing = static_cast<int>(spacing * (children.size() - 1));
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
            maxChildWidth = width - (properties.padding * 2);
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
            if (!child->IsVisible()) {
                continue;
            }

            xpos = xpos + child->GetProperties().marginLeft;
            ypos = ypos + child->GetProperties().marginTop;

            if (!child->IsPositionAbsolute()) {
                child->SetX(xpos);
                child->SetY(ypos);
            }

            if (child->IsPositionAbsolute()) {

                if (child->IsWidthResizable()) {
                    child->SetWidth(width - (properties.padding * 2) - (GetX() + child->GetLocalX()));
                }
                
                if (child->GetAnchor() == PositionMode::BottomLeft) {
                    child->SetX(GetX() + child->GetLocalX());
                    child->SetY(GetY() + GetHeight() - child->GetHeight() - child->GetProperties().marginBottom - child->GetLocalY());
                }
                else {
                    child->SetX(GetX() + child->GetLocalX());
                    child->SetY(GetY() + child->GetLocalY());
                }
               child->UpdateChildSizes();
               child->UpdateVertices();
               
                continue;
            }
            
            if (child->GetElementType() == ElementType::CONTAINER && child->IsHeightResizable())
            {
                child->SetWidth(width - (properties.padding * 2));
                child->SetHeight(flexibleHeight);
                if (!child->IsPositionAbsolute()) {
                    child->SetX(xpos);
                    child->SetY(ypos);
                }
                child->UpdateChildSizes();
            }

            if (child->GetElementType() == ElementType::CONTAINER && !child->IsHeightResizable())
            {
                if (!child->IsPositionAbsolute()) {
                    child->SetX(xpos);
                    child->SetY(ypos);
                }
                child->UpdateChildSizes();
            }

            if (child->IsHeightResizable())
            {
                child->SetHeight(flexibleHeight);
                child->UpdateChildSizes();
            }

            if (xAlign == AlignItems::Stretch)
            {
                child->SetWidth(width - (properties.padding * 2));
            }

            if (child->IsWidthResizable())
            {
                child->SetWidth(width - (properties.padding * 2) - (child->GetProperties().marginRight + child->GetProperties().marginLeft));

                if (child->GetElementType() == ElementType::CONTAINER )
                {
                    child->UpdateChildSizes();
                }
                if (xAlign == AlignItems::Center) {
                    child->SetWidth(width - xpos);
                }
            }

            if (child->GetElementType() == ElementType::BUTTON) {
                child->UpdateChildSizes();
            }

            ypos += child->GetHeight() + child->GetProperties().marginBottom;
            xpos -= child->GetProperties().marginLeft; //Reset so the next element is                                        
            if (i < children.size() - 1)                //relative to the container not the element before it
            {
                ypos += spacing ;
            }
            child->UpdateVertices();
            child->UpdateChildSizes();
        }
	}
   
}


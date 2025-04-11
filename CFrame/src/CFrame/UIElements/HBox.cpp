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

	void HBox::UpdateChildSizes()
	{
        if (children.empty())
            return;

        int fixedWidth = 0;
        int flexWidth = 0;
        int flexibleCount = 0;
        int maxChildHeight = 0;
        int totalMargins = 0; //For the flexible items

        int xpos = x + properties.padding;
        int ypos = y + properties.padding;

        for (auto* child : children)
        {
            if (!child->IsVisible() || child->IsPositionAbsolute()) {
                continue;
            }

            if (child->IsWidthResizable())
            {
                flexibleCount++;
                totalMargins += child->GetProperties().marginLeft * 2;
            }
            else
            {
                fixedWidth += child->GetWidth() + (child->GetProperties().marginLeft + child->GetProperties().marginRight);//May not be right
            }
            if (child->GetHeight() > maxChildHeight && !child->IsHeightResizable())
            {
                maxChildHeight = child->GetHeight();
            }
        }

        int totalSpacing = spacing * (children.size() - 1);
        // Width is the width of the current hbox
        int availableSpace = width - fixedWidth - totalSpacing - totalMargins - (properties.padding * 2);

        if (flexibleCount > 0)
        {
            flexWidth = (availableSpace / flexibleCount);
        }
        else
        {
            flexWidth = 0;
        }

        if (maxChildHeight == 0) {
            maxChildHeight = height - (properties.padding * 2);
        }


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

        switch (yAlign)
        {
        case AlignItems::Center:
            ypos = y + (height / 2) - (maxChildHeight / 2);
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

        

        // Assign positions to each child
        for (size_t i = 0; i < children.size(); i++)
        {
            UIElement* child = children[i];
            if (!child->IsVisible() ) {
                continue;
            }

            xpos = xpos + child->GetProperties().marginLeft; //Todo: Remove the need to constantly call GetProperties
            ypos = ypos + child->GetProperties().marginTop;

            if (!child->IsPositionAbsolute()) {
                child->SetX(xpos);
                child->SetY(ypos);
            }

            if (child->IsPositionAbsolute()) {
                if (child->IsWidthResizable()) {
                    child->SetWidth(width -child->GetLocalX() - properties.padding * 2 - child->GetProperties().marginRight);
                }
                child->SetX(GetX() + child->GetLocalX());
                child->SetY(GetY() + child->GetLocalY());

                if (child->GetElementType() == ElementType::CONTAINER) {
                    child->UpdateChildSizes();
                }
                continue;
            }
            
            if (child->GetElementType() == ElementType::CONTAINER && child->IsWidthResizable())//todo: Fix isDraggable 
            {
                if (flexWidth > child->GetProperties().maxWidth && child->GetProperties().maxWidth > 0) {
                    flexWidth = child->GetProperties().maxWidth;
                }
                child->SetWidth(flexWidth);
                child->SetHeight(height - (properties.padding * 2));
                if (!child->IsPositionAbsolute()) {
                    child->SetX(xpos);
                    child->SetY(ypos);
                }
                child->UpdateChildSizes();
            }
          

            if (child->GetElementType() == ElementType::CONTAINER && !child->IsWidthResizable())
            {
                if (!child->IsPositionAbsolute()) {
                    child->SetX(xpos);
                    child->SetY(ypos);
                }
                child->UpdateChildSizes();
            }

            if (child->IsWidthResizable())
            {
                child->SetWidth(flexWidth);
                child->UpdateChildSizes();
            }

            if (yAlign == AlignItems::Stretch)
            {
                child->SetHeight(height - (properties.padding * 2));
            }

            if (child->IsHeightResizable() || child->GetHeight() < 0)
            {
                child->SetHeight(height - (properties.padding * 2));
                child->SetX(xpos + child->GetProperties().marginLeft);
                child->SetY(ypos + child->GetProperties().marginTop);
                child->UpdateChildSizes();
            }

            if (child->GetHeight() > height) {
                child->SetHeight(height - (properties.padding * 2));
            }

            xpos += child->GetWidth() + child->GetProperties().marginRight;
            if (i < children.size() - 1)
            {
                xpos += spacing;
                //xpos-=  padding;
            }
        }
	}

	
}


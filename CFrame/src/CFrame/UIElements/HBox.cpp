#include "HBox.h"
namespace CFrame {

	HBox::HBox(int x, int y, int w, int h, UIElement* parent)
		:Container(x,y,w,h, parent)
	{
		isHeightResizable = true; //Todo adjust based on if it was provided
		isWidthResizable = true;
	}

	HBox::~HBox()
	{

	}

	void HBox::Render(Renderer& renderer)
	{
		renderer.DrawRectangle(x, y, width, height, { 0,0,255,255 }, 0.0, 0);
		for (auto& child : children) {
			child->Render(renderer);
		}
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
            if (child->IsWidthResizable())
            {
                flexibleCount++;
                totalMargins += child->GetProperties().marginLeft * 2;
            }
            else
            {
                fixedWidth += child->GetWidth() + (child->GetProperties().marginLeft + properties.marginRight);//May not be right
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

            child->SetX(xpos + child->GetProperties().marginLeft);
            child->SetY(ypos + child->GetProperties().marginTop);

            //Store UIconatainer into a variable so oly check once

            if (dynamic_cast<Container*>(child) && child->IsWidthResizable())
            {
                child->SetWidth(flexWidth);
                child->SetHeight(height - (properties.padding * 2));
                child->SetX(xpos);
                child->SetY(ypos);
                child->UpdateChildSizes();
            }

            if (dynamic_cast<Container*>(child) && !child->IsWidthResizable())
            {
                child->SetX(xpos);
                child->SetY(ypos);
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

            xpos += child->GetWidth();
            if (i < children.size() - 1)
            {
                xpos += spacing;
                //xpos-=  padding;
            }
        }
	}

	void HBox::OnEvent(CFrameEvent& event)
	{


	}
}


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

	void HBox::Render(Renderer& renderer)
	{
		renderer.DrawRectangle(x, y, width, 
            height, properties.color1.toSDLColor(255), 
            properties.color1.toSDLColor(255),0.0, 
            properties.radius, 
            1.0f, 1.0f, 0.0,
            properties.color1.toSDLColor(255),
            properties.color1.toSDLColor(255));

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

            xpos = xpos + child->GetProperties().marginLeft; //Todo: Remove the need to constantly call GetProperties
            ypos = ypos + child->GetProperties().marginTop;

            child->SetX(xpos);
            child->SetY(ypos);

            if (child->GetElementType() == ElementType::CONTAINER && child->IsWidthResizable())
            {
                if (flexWidth > child->GetProperties().maxWidth) {
                    flexWidth = child->GetProperties().maxWidth;
                }
                child->SetWidth(flexWidth);
                child->SetHeight(height - (properties.padding * 2));
                child->SetX(xpos);
                child->SetY(ypos);
                child->UpdateChildSizes();
            }

            if (child->GetElementType() == ElementType::CONTAINER && !child->IsWidthResizable())
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
        for (auto& child : children) {
            if (event.handled)  return;

            child->OnEvent(event);
        }

	}
}


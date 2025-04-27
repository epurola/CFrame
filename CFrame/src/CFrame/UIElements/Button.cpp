#include "Button.h"
#include <algorithm>
#include "../Renderer/FontLoader.h"
#include "../Renderer/FontManager.h"


namespace CFrame 
{
	Button::Button(int x, int y, int w, int h, const std::string& text, 
          std::function<void()> onClick, UIElement* parent) 
		:UIElement(x, y, w, h, parent), onClick(onClick), text(text),
        animator(std::make_unique<Animator>(*this))
	{
        isWidthResizable = (w == -1);
        isHeightResizable = (h == -1);
		SetRadius(15,15,15,15);
        SetColor(Color::Gray);

	}

	Button::~Button()
	{

	}

    void Button::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
    {
        applicationManager = manager;
    }

    //For everytime button change change font size and position not everyframe.
	void Button::Render(Renderer& renderer)
	{
        int renderWidth  = width;
        int renderHeight = height;

        if (!animProperties.isAnimatedElement) {
             renderWidth  = static_cast<int>(width * properties.scaleX);
             renderHeight = static_cast<int>(height * properties.scaleY);
        }
       
        if (animator->IsAnimating()) {
            animator->Update(0.016f); //60fps
        }

        int centeredX = x + (width - renderWidth) / 2;
        int centeredY = y + (height - renderHeight) / 2;
        

		renderer.DrawRectangle((float)centeredX, (float)centeredY , (float)renderWidth, (float)renderHeight, 
            GetProperties(),
            animator->GetTime(), 
            animProperties.speed,
            imageTexture.get());


       renderer.RenderText(text, (float)centeredX, (float)centeredY, textProps, labelTexture.get(), overflow );
	}

    void Button::UpdateChildSizes()
    {
        if (!labelTexture) {
            FontKey key = { textProps.font, textProps.fontSize };
            FontManager& fm = FontManager::GetInstance();
            std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>> font = fm.GetFont(key);
            glyphs = font.second; //Info about the glyph and where it is in the atlas
            labelTexture = font.first;
        }
       
        if (!overflow.overflow) {
            overflow.clipHeight = height;
            overflow.clipWidth  = width;
            overflow.clipX      = x;
            overflow.clipY      = y;
        }

          
            float offsetX = 0.0f, offsetY = 0.0f;
            int textWidth = 0, textHeight = 0;
            textProps.textWidth = 0;
            textProps.textHeight = 0;
            textProps.vertices.clear();
            textProps.indices.clear();
            //ToDo: Determine if you need to use the text or icon icons have PUA range

            for (char c : text) {
                fontInfo glyph = glyphs[c];

                float charWidth = (float)glyph.width;
                float charHeight = (float)glyph.height;
                textProps.textWidth += glyph.advance;
                textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
            }

            if (textProps.textAlign == TextAlign::Center) {
                offsetX = (float)(width / 2) - (textProps.textWidth / 2);
                offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f); //OpneGl goes from down up and screen up down so flip this
            }
            else if (textProps.textAlign == TextAlign::Start) {
                offsetX = (float)properties.padding;
                offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
            }
            else {
                offsetX = (float)width - textProps.textWidth - properties.padding;
                offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
            }

            for (char c : text) {
                //Store the current glyph info
                fontInfo glyph = glyphs[c];
                if (icon.has_value()) {
                     glyph = glyphs[icon.value()];
                }

                //texture coordinates for the character
                float texX1 = glyph.x / (float)labelTexture->GetWidth(); // width
                float texY1 = glyph.y / (float)labelTexture->GetHeight(); //height
                float texX2 = (glyph.x + glyph.width) / (float)labelTexture->GetWidth();
                float texY2 = (glyph.y + glyph.height) / (float)labelTexture->GetHeight();

                float charWidth = (float)glyph.width;
                float charHeight = (float)glyph.height;

                float xpos = GetX() + offsetX + glyph.bearingX;
                float ypos = GetY() + offsetY + (charHeight - glyph.bearingY);

                float w = (float)glyph.width;   // actual width of the glyph quad
                float h = (float)glyph.height;  // actual height of the glyph quad

                float leftX = xpos;
                float rightX = xpos + w;
                float topY = ypos;
                float bottomY = ypos - h;
               
                //Define 4 vertices for the current character
                textProps.vertices.push_back(leftX);                   //top-Left x
                textProps.vertices.push_back(topY);                    //Top-Left y
                textProps.vertices.push_back(texX1);                   //Texture coord x1
                textProps.vertices.push_back(texY2);                   //Texture coord y2

                textProps.vertices.push_back(rightX);                  //Top-Right x
                textProps.vertices.push_back(topY);                    //Top-Right y
                textProps.vertices.push_back(texX2);                   //texture coord x2
                textProps.vertices.push_back(texY2);                   //texture coord y2

                textProps.vertices.push_back(rightX);                  //Bottom-Right x
                textProps.vertices.push_back(bottomY);
                textProps.vertices.push_back(texX2);                   //texture coord x2
                textProps.vertices.push_back(texY1);                   //texture coord y1

                textProps.vertices.push_back(leftX);                   //Bottom-Left x
                textProps.vertices.push_back(bottomY);                 //bottom-Right y
                textProps.vertices.push_back(texX1);                   //Texture coord x1
                textProps.vertices.push_back(texY1);                   //Texture coord y1

                unsigned int baseIndex = (unsigned int)(textProps.vertices.size() / 4) - 4;
                textProps.indices.push_back(baseIndex);                // 0
                textProps.indices.push_back(baseIndex + 1);            // 1
                textProps.indices.push_back(baseIndex + 2);            // 2
                textProps.indices.push_back(baseIndex + 2);            // 2
                textProps.indices.push_back(baseIndex + 3);            // 3
                textProps.indices.push_back(baseIndex);                // 0

                offsetX += glyph.advance;
            }
    }

    void Button::OnEvent(CFrameEvent& event)
    {
 
       //Add early return if not tracked event

        if (event.GetEventType() == CFrameEventType::MouseButtonDown) {

            auto* mouseEvent = dynamic_cast<MouseButtonDownEvent*>(&event);
            if (!mouseEvent) {
                return; // Early return if the event is not a MouseButtonDownEvent
            }

            int xPos = static_cast<int>(mouseEvent->GetX());
            int yPos = static_cast<int>(mouseEvent->GetY());

            // Check if the mouse position is inside the button's bounds
            if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
                return; // Early return if the click is outside the button
            }

            //call the onClick handler
            CF_CORE_INFO("Button Clicked!");
            if (onClick) {
                onClick();
            }
            event.handled = true;
        }
        if (event.GetEventType() == CFrameEventType::MouseMoved) {

            auto* mouseEvent = dynamic_cast<MouseMovedEvent*>(&event);
            if (!mouseEvent) {
                return; // Early return if the event is not a MouseButtonDownEvent
            }

            int xPos = static_cast<int>(mouseEvent->GetX());
            int yPos = static_cast<int>(mouseEvent->GetY());

            // Check if the mouse position is inside the button's bounds
            if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
                if (hovering) { 
                    onLeave();
                    hovering = false;
                    applicationManager->RemoveAnimator(*this);
                }
                return;
            }
            hovering = true;
            //call the onClick handler
            if (onHover ) {
                onHover(); 
                if (animProperties.speed > 0 ) {
                    applicationManager->RegisterAnimation(*this);
                }  
            }
            event.handled = true;
        }
        if (event.GetEventType() == CFrameEventType::MouseLeaveWindow) {
            if (hovering) {
                onLeave();
                hovering = false;
                applicationManager->RemoveAnimator(*this);
            }
        }
    }

    void Button::SetOnClick(std::function<void()> onClick)
    {
        this->onClick = onClick;
    }

    void Button::StartAnimation()
    {
        animator->StartAnimation(animProperties.duration);
    }

    void Button::SetText(std::string text)
    {
        this->text = text;
    }

    void Button::SetIcon(int codePoint)
    {
        icon = codePoint;
        SetText(" ");
        SetFont(Font::SegoeMDL2Assets);
    }

    void Button::setTextOpacity(float opacity)
    {
        textProps.opacity = opacity;
    }

    void Button::SetFontSize(float size)
    {
        textProps.fontSize = size;
    }

    void Button::SetFont(Font font)
    {
        textProps.font = font;
    }

   
}




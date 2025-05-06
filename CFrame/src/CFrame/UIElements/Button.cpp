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
        SetFontSize(24);
        SetIsDirty(true);
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

        //What?
        if (!animProperties.isAnimatedElement) 
        {
            renderWidth  = static_cast<int>(width * properties.scaleX);
            renderHeight = static_cast<int>(height * properties.scaleY);
        }
       
        if (animator->IsAnimating()) 
        {
            animator->Update(0.016f); //60fps
        }

        int centeredX = x + (width - renderWidth) / 2;
        int centeredY = y + (height - renderHeight) / 2;
        
		renderer.DrawRectangle((float)centeredX, (float)centeredY , (float)renderWidth, (float)renderHeight, 
            GetProperties(),
            animator->GetTime(), 
            animProperties.speed,
            imageTexture.get());

       renderer.RenderText(text, (float)centeredX, (float)centeredY, textProps, atlasTexture.get(), overflow );
	}

    // toDo; Refactor this
    void Button::UpdateChildSizes()
    {
        if (!atlasTexture) 
        {
            InitAtlasTexture();
        }
       
        SetOverFlowProperties();

         float offsetX = 0.0f, offsetY = 0.0f;
         int textWidth = 0, textHeight = 0;
         textProps.textWidth = 0;
         textProps.textHeight = 0;
         textProps.vertices.clear();
         textProps.indices.clear();
         
         for (char c : text) 
         {
             fontInfo glyph = glyphs[c];
             float charWidth = (float)glyph.width;
             float charHeight = (float)glyph.height;
             textProps.textWidth += glyph.advance;
             textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
         }

         if (textProps.textAlign == TextAlign::Center) 
         {
             offsetX = (float)(width / 2) - (textProps.textWidth / 2);
             offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f); //OpneGl goes from down up and screen up down so flip this
         }
         else if (textProps.textAlign == TextAlign::Start) 
         {
             offsetX = (float)properties.padding;
             offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
         }
         else 
         {
             offsetX = (float)width - textProps.textWidth - properties.padding;
             offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
         }

         for (char c : text) 
         {
             //Store the current glyph info
             fontInfo glyph = glyphs[c];
             if (icon.has_value()) 
             {
                  glyph = glyphs[icon.value()];
             }

             //texture coordinates for the character
             float texX1 = glyph.x / atlasWidth; 
             float texY1 = glyph.y / atlasHeight; 
             float texX2 = (glyph.x + glyph.width) / atlasWidth;
             float texY2 = (glyph.y + glyph.height) / atlasHeight;

             float charWidth = (float)glyph.width;
             float charHeight = (float)glyph.height;

             float xpos = GetX() + offsetX + glyph.bearingX;
             float ypos = GetY() + offsetY + (charHeight - glyph.bearingY);

             float leftX = xpos;
             float rightX = xpos + charWidth;
             float topY = ypos;
             float bottomY = ypos - charHeight;
            
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
        if (event.handled)  return;

        switch (event.GetEventType()) 
        {
            case CFrameEventType::MouseButtonDown: 
            {
                auto& mouseEvent = static_cast<MouseButtonDownEvent&>(event);
                event.handled = HandleMouseButtonDown(mouseEvent);
                return;
            }

            case CFrameEventType::MouseMoved: 
            {
                auto& mouseEvent = static_cast<MouseMovedEvent&>(event);
                event.handled = HandleMouseMove(mouseEvent); //Return false everytime to avoid buttons with old frames
                return;
            }

            case CFrameEventType::MouseLeaveWindow: 
            {
                event.handled = HandleMouseLeaveWindow(); //Also returns false so other elements can get this
                return;
            }
        }
        return;
    }

    bool Button::HandleMouseButtonDown(MouseButtonDownEvent& e)
    {
        int xPos = static_cast<int>(e.GetX());
        int yPos = static_cast<int>(e.GetY());

        // Early return if the click is outside the button
        if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) return false; 
        
        if (onClick) 
        {
            onClick();
        }
        return true;
    }

    bool Button::HandleMouseLeaveWindow()
    {
        if (hovering) 
        {
            onLeave();
            hovering = false;
            applicationManager->RemoveAnimator(*this);
        }
        return false;
    }

    bool Button::HandleMouseMove(MouseMovedEvent& e)
    {
        int xPos = static_cast<int>(e.GetX());
        int yPos = static_cast<int>(e.GetY());

        // Check if the mouse position is inside the button's bounds
        if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) 
        {
            if (hovering) 
            {
                onLeave();
                hovering = false;
                applicationManager->RemoveAnimator(*this);
            }
            return false;
        }

        hovering = true;

        if (onHover) 
        {
            onHover();
            if (animProperties.speed > 0) 
            {
                applicationManager->RegisterAnimation(*this);
            }
            return false;
        }
    }

    void Button::InitAtlasTexture()
    {
        FontKey key = { textProps.font, textProps.fontSize };
        FontManager& fm = FontManager::GetInstance();
        std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>> font = fm.GetFont(key);
        glyphs = font.second; //Info about the glyph and where it is in the atlas
        atlasTexture = font.first;

        atlasWidth = atlasTexture->GetWidth();
        atlasHeight = atlasTexture->GetHeight();
    }

    void Button::SetOverFlowProperties()
    {
        if (!overflow.overflow)
        {
            overflow.clipHeight = height;
            overflow.clipWidth = width;
            overflow.clipX = x;
            overflow.clipY = y;
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




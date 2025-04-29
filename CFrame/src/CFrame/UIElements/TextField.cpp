#include "TextField.h"

namespace CFrame 
{
	TextField::TextField(int x, int y, int w, int h, UIElement* parent)
		:UIElement(x,y,w,h,parent)
	{
		isWidthResizable = (w == -1);
		isHeightResizable = (h == -1);
        SetColor(Color::White, Color::White);
        SetTextColor(Color::White);
        SetRadius(20,20,20,20);
        SetPadding(10);

        lineProperties.color = Color::Blue; 
        cursorHeight = 20;
        textProps.textHeight = 0;


	}

	TextField::~TextField()
	{

	}

	void TextField::Render(Renderer& renderer)
	{
        if (!overflow.overflow) {
            overflow.clipHeight = height;
            overflow.clipWidth = width;
            overflow.clipX = x;
            overflow.clipY = y;
        }

		renderer.DrawRectangle(x, y, width, height ,properties, 1.0f, 1.0f, nullptr);
		renderer.RenderText(input, x, y, textProps, labelTexture.get(), overflow);
        
        if (isActive) {
            elapsedTime += 0.016f;
            if (elapsedTime > 1.0f) {
                elapsedTime = 0.0f;
            }
            if (elapsedTime < 0.5f) {
                renderer.DrawLine(lineProperties);
            }
        }
	}

    void TextField::OnEvent(CFrameEvent& event)  
    {  
        if (event.GetEventType() == CFrameEventType::MouseButtonDown) {

            auto* mouseEvent = dynamic_cast<MouseButtonDownEvent*>(&event);
            if (!mouseEvent) {
                return; // Early return if the event is not a MouseButtonDownEvent
            }

            int xPos = static_cast<int>(mouseEvent->GetX());
            int yPos = static_cast<int>(mouseEvent->GetY());

            if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
                isActive = false;
                applicationManager->RemoveAnimator(*this);
                applicationManager->DeActivatetextInput();
                return; 
            }
            if (isActive) {
                isActive = false;
                applicationManager->RemoveAnimator(*this);
                return;
            }
            applicationManager->RegisterAnimation(*this);
            applicationManager->ActivateTextInput();
            isActive = true;
        }

       if (event.GetEventType() == CFrameEventType::TextInput) {  
           auto* keyEvent = dynamic_cast<TextInputEvent*>(&event);  
           if (keyEvent) {  
               input += keyEvent->GetChar();   
               //UpdateChildSizes();
               AddCharacter(keyEvent->GetChar());
               event.handled = true;
           }  
       }  

       if (horizontalScroll) {
           if (event.GetEventType() == CFrameEventType::MouseScroll) {
               auto* mouseEvent = dynamic_cast<MouseScrolledEvent*>(&event);
               if ((mouseEvent->GetMouseX() >= x && mouseEvent->GetMouseX() <= x + width) &&
                   (mouseEvent->GetMouseY() >= y && mouseEvent->GetMouseY() <= y + height))
               {
                   UpdateVertexX(mouseEvent->GetDistanceX() * 15);
                   event.handled = true;
               }
           }
       }

       if (verticalScroll) {
           if (event.GetEventType() == CFrameEventType::MouseScroll) {
               auto* mouseEvent = dynamic_cast<MouseScrolledEvent*>(&event);
               if ((mouseEvent->GetMouseX() >= x && mouseEvent->GetMouseX() <= x + width) &&
                   (mouseEvent->GetMouseY() >= y && mouseEvent->GetMouseY() <= y + height))
               {
                   UpdateVertexY(mouseEvent->GetDistanceY());
                   event.handled = true;
               }
           }
       }

      
    }

	void TextField::UpdateChildSizes()
	{
        if (!labelTexture) {
            FontKey key = { textProps.font, textProps.fontSize };
            FontManager& fm = FontManager::GetInstance();
            std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>> font = fm.GetFont(key);
            glyphs = font.second; //Info about the glyph and where it is in the atlas
            labelTexture = font.first;
           //Predetermine the tallest char for the AddCharFunction.
            for (char c : "qwertyuiopasdfghjklöäzxcvbnmASDFGHJKLÖQWERTYUIOPZXCVBNM") {
                fontInfo glyph = glyphs[c];
                float charHeight = (float)glyph.height;
                textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
            }
            //Set OffsetY based on the tallest one
            offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
            offsetX = (float)properties.padding;
            
        }
        //Recalculate when the textField size changes
        for (char c : input) {
            fontInfo glyph = glyphs[c];
            float charWidth = (float)glyph.width;
            float charHeight = (float)glyph.height;
            textProps.textWidth += glyph.advance;
            textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
        }

        offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
        offsetX = (float)properties.padding;

        //Clear the vectors 
        textProps.vertices.clear();
        textProps.indices.clear();
        textWidth = textProps.textWidth;
        lineNumber = 0;
        
        for (char c : input) {
            AddCharacter(c);
        }

        UpdateCursorPosition(offsetX);
	}

	void TextField::SetIsActive(bool b)
	{
		isActive = b;
	}

    void TextField::AddCharacter(char c)
    {
        fontInfo glyph = glyphs[c];
        
        //texture coordinates for the character
        float texX1 = glyph.x / (float)labelTexture->GetWidth(); // width
        float texY1 = glyph.y / (float)labelTexture->GetHeight(); //height
        float texX2 = (glyph.x + glyph.width) / (float)labelTexture->GetWidth();
        float texY2 = (glyph.y + glyph.height) / (float)labelTexture->GetHeight();

        textWidth = textProps.textWidth;
        
        float charWidth = (float)glyph.width;
        float charHeight = (float)glyph.height;

        if (isHeightResizable) {
            if ((offsetX + glyph.advance + glyph.bearingX) > width - properties.padding) {
                lineNumber++;
                offsetX = (float)properties.padding; // Reset to start
                UpdateVertexY(textProps.textHeight + lineSpacing); //Update old lines position
            }
        }
        else {
            if ((offsetX + glyph.advance + glyph.bearingX) > width - properties.padding){
                UpdateVertexX(glyph.advance); //Update old lines position
                //UpdateCursorPosition() ToDo fix this method
                offsetX -= glyph.advance;
            }
        }
        

        float xpos = GetX() + offsetX + glyph.bearingX;
        float ypos = GetY() + offsetY + (charHeight - glyph.bearingY);

        float w = (float)glyph.width;   // actual width of the glyph quad
        float h = (float)glyph.height;  // actual height of the glyph quad

        float leftX = xpos;
        float rightX = xpos + w;
        float topY = ypos;
        float bottomY = ypos - h;

        textProps.vertices.push_back(leftX);                   //top-Left x
        textProps.vertices.push_back(topY);                   //Top-Left y
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

        UpdateCursorPosition(offsetX);
    }

    void TextField::UpdateCursorPosition(int offset)
    {
        lineProperties.vertices.topLeft.x = x + offset;
        lineProperties.vertices.bottomLeft.x = x + offset;
        lineProperties.vertices.topRight.x = x + offset + 3;
        lineProperties.vertices.bottomRight.x = x + offset + 3;
        //Reset to match font height
        lineProperties.vertices.topLeft.y = y + (cursorHeight);
        lineProperties.vertices.topRight.y = y + (cursorHeight);
        lineProperties.vertices.bottomLeft.y = y + height - (cursorHeight);
        lineProperties.vertices.bottomRight.y = y + height - (cursorHeight);
    }


    void TextField::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
    {
        applicationManager = manager;
    }

    void TextField::SetInput(const std::string& value)
    {

    }
    void TextField::UpdateVertexY(int offset)
    {
        int floatsPerVertex = 4;  // (x, y, u, v)
        int i = 0;

            for (float& v : textProps.vertices) {
                if ((i % floatsPerVertex) == 1) {
                    v -= offset;
                }
                i++;
            }
    }
    void TextField::UpdateVertexX(int offset)
    {
        int floatsPerVertex = 4;  // (x, y, u, v)
        int i = 0;

        for (float& v : textProps.vertices) {
            if ((i % floatsPerVertex) == 0) {
                v -= offset;
            }
            i++;
        }
    }
}


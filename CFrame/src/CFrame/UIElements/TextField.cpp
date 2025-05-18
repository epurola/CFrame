#include "TextField.h"
#include "../RenderAPI/Renderer2D.h"

namespace CFrame 
{
	TextField::TextField(int x, int y, int w, int h, UIElement* parent)
		:UIElement(x,y,w,h,parent)
	{
		isWidthResizable = (w == -1);
		isHeightResizable = (h == -1);
        SetColor(Color::White, Color::White);
        SetTextColor(Color::White);
        SetRadius(10,10,10,10);
        SetPadding(10);
        SetBorder(1);
        SetBorderColor(Color::LightGray);
        SetFontSize(29);

        lineProperties.color = Color::Blue; 
        cursorHeight = 20;
        textProps.textHeight = 0;
        characters.reserve(1024);
        textProps.vertices.reserve(1024); 
        textProps.indices.reserve(1024);

	}

	TextField::~TextField()
	{

	}

	void TextField::Render(Renderer1& renderer)
	{
		renderer.DrawRectangle(x, y, width, height ,properties, 1.0f, 1.0f, nullptr);
		renderer.RenderText( x, y, textProps, atlasTexture.get(), overflow);
        
        if (isActive) 
        {
            elapsedTime += 0.016f;

            if (elapsedTime > 1.0f) 
            {
                elapsedTime = 0.0f;
            }
            if (elapsedTime < 0.5f) 
            {
                renderer.DrawLine(lineProperties);
            }
        }
	}

    void TextField::Render(float timestep)
    {
        QuadInstance instance{};

        instance.position = { x, y };
        instance.size = { width * properties.scaleX, height * properties.scaleY };

        // Base colors (RGBA)
        instance.color1 = properties.colors.background1;
        instance.color2 = properties.colors.background2;

        // Border colors 
        instance.borderColor1 = properties.colors.border1;
        instance.borderColor2 = properties.colors.border2;

        instance.borderSizes = { properties.border.top, properties.border.right, properties.border.bottom, properties.border.left };

        // Radius for corners
        instance.radius = { properties.radius.topLeft, properties.radius.topRight, properties.radius.bottomLeft, properties.radius.bottomRight };

        // Animation parameters
        instance.time = 0.0f;  //  pass actual elapsed time
        instance.speed = 0.0f;
        instance.angle = 0.0f;

        Renderer2D::DrawQuad(instance);
        Renderer2D::DrawTex({ (float)x, (float)y, textProps, atlasTexture.get(), overflow });
    }

    void TextField::OnEvent(CFrameEvent& event)  
    {  
        if (event.handled)  return;

        switch (event.GetEventType()) 
        {
            case CFrameEventType::TextInput: 
            {
                auto& keyEvent = static_cast<TextInputEvent&>(event);
                event.handled = HandleTextInput(keyEvent);
                return;
            }

            case CFrameEventType::MouseButtonDown: 
            {
                auto& mouseEvent = static_cast<MouseButtonDownEvent&>(event);
                event.handled = HandleMouseButtonDown(mouseEvent);
                return;
            }

            case CFrameEventType::KeyPressed: 
            {
                auto& keyEvent = static_cast<KeyPressedEvent&>(event);
                event.handled = HandleKeyPressed(keyEvent);
                return;
            }

            case CFrameEventType::MouseScroll: 
            {
                auto& mouseEvent = static_cast<MouseScrolledEvent&>(event);
                event.handled = HandleMouseScroll(mouseEvent);
                return;
            }
        }
        return;
    }

	void TextField::UpdateChildSizes()
	{
        //Do here to make sure there is a valid OpenGl context
        if (!atlasTexture) {
            InitializeAtlas();
        }
        
        SetOverFlowProperties();
        //Needed for text wrapping so text length is updated
        // textProps.textWidth = 0;
        // textProps.textHeight = 0;
        // UpdateTextProperties();

        offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
        offsetX = (float)properties.padding;

        //Clear the vectors 
        textProps.vertices.clear();
        textProps.indices.clear();
        characters.clear();
        textWidth = textProps.textWidth;
        lineNumber = 0;

        int index = 0;
        for (char c : input) 
        {
            AddCharacter(c , index);
            index++;
        }
	}

    void TextField::AddCharacter(char c, int index)
    {
        fontInfo glyph = glyphs[c];
        
        //texture coordinates for the character
        float texX1 = glyph.x / atlasWidth; 
        float texY1 = glyph.y / atlasHeight; 
        float texX2 = (glyph.x + glyph.width) / atlasWidth;
        float texY2 = (glyph.y + glyph.height) / atlasHeight;

        textWidth = textProps.textWidth;
        
        float charWidth = (float)glyph.width;
        float charHeight = (float)glyph.height;

        if (isHeightResizable) 
        {
            if ((offsetX + glyph.advance + glyph.bearingX) > width - properties.padding) 
            {
                lineNumber++;
                offsetX = (float)properties.padding; // Reset to start
                UpdateVertexY(textProps.textHeight + lineSpacing); //Update old lines position
            }
        }
        else 
        {
            if ((offsetX + glyph.advance + glyph.bearingX) > width - properties.padding)
            {
                UpdateVertexX(glyph.advance); //Update old lines position
                offsetX -= glyph.advance;
            }
        }
        
        float xpos = GetX() + offsetX + glyph.bearingX;
        float ypos = GetY() + offsetY + (charHeight - glyph.bearingY);

        float leftX = xpos;
        float rightX = xpos + charWidth;
        float topY = ypos;
        float bottomY = ypos - charHeight;

        Character  q;
        q.advance = glyph.advance;
        q.character = c;
        q.x = leftX;
        q.visible = leftX  > x ? true : false;

        if (index >= characters.size()) 
        {
            characters.resize(index + 1);  
        }

        characters[index] = q;
       
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

        AccumulateCursorPosition(offsetX);
    }

    //Todo keep track of curr line and only search that
    void TextField::UpdateCursorPosition(int index)
    {
        if (index < 0) index = 0;
        if (index >= characters.size()) index = (int)characters.size();

        float cursorX = characters.empty() || index == 0
            ? x + properties.padding
            : characters[index - 1 ].x + characters[index - 1].advance;

        lineProperties.vertices.topLeft.x = cursorX;
        lineProperties.vertices.bottomLeft.x = cursorX;
        lineProperties.vertices.topRight.x = cursorX + 3;
        lineProperties.vertices.bottomRight.x = cursorX + 3;

        //Reset to match font height
        lineProperties.vertices.topLeft.y = y + (cursorHeight);
        lineProperties.vertices.topRight.y = y + (cursorHeight);
        lineProperties.vertices.bottomLeft.y = y + height - (cursorHeight);
        lineProperties.vertices.bottomRight.y = y + height - (cursorHeight);
    }

    void TextField::AccumulateCursorPosition(int offset)
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

    int TextField::GetCharacterIndex(int cursorX)
    {
        for (int i = 0; i < characters.size(); i++) 
        {
            auto& ch = characters[i];
            float charMid = ch.x + ch.advance * 0.5f;
           
            if (cursorX < charMid) 
            {
                currIndex = i ; 
                return i;      
            }
        }
        currIndex = input.size();
        return (int)characters.size();
    }

    bool TextField::HandleMouseButtonDown(MouseButtonDownEvent& e)
    {
        int xPos = static_cast<int>(e.GetX());
        int yPos = static_cast<int>(e.GetY());

        if (xPos < x || xPos >(x + width) || yPos < y || yPos >(y + height)) {
            isActive = false;
            applicationManager->RemoveAnimator(*this);
            applicationManager->DeActivatetextInput();
            return false; // Event was not handled by this just deactivated the input reading
        }

        if (isActive) {
            int i = GetCharacterIndex(xPos);
            UpdateCursorPosition(i);
            return true;
        }

        applicationManager->RegisterAnimation(*this);
        applicationManager->ActivateTextInput();
        isActive = true;
        return true;
    }

    bool TextField::HandleTextInput(TextInputEvent& e)
    {
        char c = e.GetChar();
        if (currIndex == input.size() - 1) {
            AddCharacter(c, currIndex);
        }
        else 
        {//Handle inserts in the middle of the string
            input.insert(currIndex, 1, c);
            UpdateChildSizes();
            UpdateCursorPosition(currIndex + 1);
        }
        currIndex++;
        return true;
    }

    bool TextField::HandleKeyPressed(KeyPressedEvent& e)
    {
        switch (e.GetKeyCode()) 
        {
             case CF_Key_BACKSPACE:
             {
                 if (input.empty()) return false;

                 // Check if we are in the visible range for the current index 
                 if (!(lineProperties.vertices.topLeft.x > x + properties.padding)) return false;

                 //Erase the character and update currIndex
                  currIndex = std::max(currIndex - 1, 0);
                  input.erase(currIndex, 1);

                  // Erase the character from the characters vector
                  if (currIndex < characters.size())
                  {
                      characters.erase(characters.begin() + currIndex);
                  }
                 
                 UpdateChildSizes();
                 UpdateCursorPosition(currIndex);
                 return true;
             }
        }
        return false;
    }

    bool TextField::HandleMouseScroll(MouseScrolledEvent& e) {
        // Check if the mouse is within the bounds of the TextField.
        bool isInBounds = (e.GetMouseX() >= x && e.GetMouseX() <= x + width) &&
            (e.GetMouseY() >= y && e.GetMouseY() <= y + height);

        if (!isInBounds) return false;
        
        if (horizontalScroll) {
            UpdateVertexX(e.GetDistanceX() * 15);
            return true;
        }

        if (verticalScroll) {
            UpdateVertexY(e.GetDistanceY());
            return true;
        }

        return false;
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

        for (float& v : textProps.vertices) 
        {
            if ((i % floatsPerVertex) == 1) 
            {
                v -= offset;
            }
            i++;
        }
    }

    void TextField::UpdateVertexX(int offset)
    {
        int floatsPerVertex = 4;  // (x, y, u, v)
        int i = 0;

        for (float& v : textProps.vertices) 
        {
            if ((i % floatsPerVertex) == 0) 
            {
                v -= offset;
            }
            i++;
        }
        //Also update the charactr vector
        for (Character& ch : characters) 
        {
            ch.x -= offset;
        }
    }

    void TextField::InitializeAtlas()
    {
        FontKey key = { textProps.font, textProps.fontSize };
        FontManager& fm = FontManager::GetInstance();
        std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>> font = fm.GetFont(key);

        //Info about the glyph and where it is in the atlas
        glyphs = font.second; 
        atlasTexture = font.first;

        //Predetermine the tallest char for the AddCharFunction.
        for (char c : "qwertyuiopasdfghjklöäzxcvbnmASDFGHJKLÖQWERTYUIOPZXCVBNM") 
        {
            fontInfo glyph = glyphs[c];
            float charHeight = (float)glyph.height;
            textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
        }

        //Set OffsetY based on the tallest one
        offsetY = (float)(height / 2.0f) + (textProps.textHeight / 2.0f);
        offsetX = (float)properties.padding;

        atlasWidth = atlasTexture->GetWidth();
        atlasHeight = atlasTexture->GetHeight();
    }

    void TextField::UpdateTextProperties()
    {
        for (char c : input) 
        {
            fontInfo glyph = glyphs[c];
            float charWidth = (float)glyph.width;
            float charHeight = (float)glyph.height;
            textProps.textWidth += glyph.advance;
            textProps.textHeight = (int)std::max((float)textProps.textHeight, charHeight);
        }
    }

    void TextField::SetOverFlowProperties()
    {
        if (!overflow.overflow)
        {
            overflow.clipHeight = height;
            overflow.clipWidth = width;
            overflow.clipX = x;
            overflow.clipY = y;
        }
    }

    void TextField::SetIsActive(bool b)
    {
        isActive = b;
    }

    void TextField::SetFontSize(float size)
    {
        textProps.fontSize = size;
    }
}


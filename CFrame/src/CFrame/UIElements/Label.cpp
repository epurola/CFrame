#include "Label.h"


namespace CFrame 
{

	Label::Label(int x, int y, int w, int h, const std::string& text, UIElement* parent)
		:UIElement(x,y,w,h,nullptr)
	{
        SetOpacity(0);
	}

	Label::~Label()
	{

	}
	void Label::Render(Renderer& renderer)
	{
        renderer.DrawRectangle(x, y, width, height, GetProperties(), 0.0f, 0.0f, labelTexture.get());
	}

    void Label::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
    {
        applicationManager = manager;
    }

	void Label::OnEvent(CFrameEvent& event)
	{

	}

	void Label::UpdateChildSizes() {

        if (!labelTexture) {
            FontKey key = { textProps.font, textProps.fontSize };
            FontManager& fm = FontManager::GetInstance();
            std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>> font = fm.GetFont(key);
            glyphs = font.second; //Info about the glyph and where it is in the atlas
            labelTexture = font.first;
        }

        if (!overflow.overflow) {
            overflow.clipHeight = height;
            overflow.clipWidth = width;
            overflow.clipX = x;
            overflow.clipY = y;
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
}


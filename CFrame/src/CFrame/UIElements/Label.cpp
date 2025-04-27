#include "Label.h"


namespace CFrame 
{

	Label::Label(int x, int y, int w, int h, const std::string& text, UIElement* parent)
		:UIElement(x,y,w,h,nullptr)
	{
		
	}

	Label::~Label()
	{

	}
	void Label::Render(Renderer& renderer)
	{
		
	}

    void Label::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
    {

    }

	void Label::CreateTexture(const std::string& text, int w, int h)
	{
		
	}
	void Label::OnEvent(CFrameEvent& event)
	{

	}

	void Label::UpdateChildSizes() {
        if (!labelTexture) {
            fontLoader = std::make_unique< FontLoader>("C:/dev/CFrame/CFrame/src/CFrame/res/fonts/arial.ttf", textProps.fontSize);
            fontLoader->LoadFont();
            std::vector<uint8_t>atlas = fontLoader->GetFontAtlas();
            glyphs = fontLoader->GetGlyphs();
            labelTexture = std::make_unique<Texture>(atlas.data(), fontLoader->GetAtlasWidth(), fontLoader->GetAtlasHeight());
        }
        float offsetX = 0.0f, offsetY = 0.0f;
        int textWidth = 0, textHeight = 0;
        textProps.textWidth = 0;
        textProps.textHeight = 0;
        textProps.vertices.clear();
        textProps.indices.clear();

        for (char c : text) {
            fontInfo glyph = glyphs[c];

            float charWidth = glyph.width;
            float charHeight = glyph.height;
            textProps.textWidth += glyph.advance;
            textProps.textHeight = std::max((float)textProps.textHeight, charHeight);

        }

        offsetX = (width / 2) - (textProps.textWidth / 2);
        offsetY = (height / 2.0f) + (textProps.textHeight / 2.0f); //OpneGl goes from down up and screen up down so flip this

        for (char c : text) {
            //Store the current glyph info
            fontInfo glyph = glyphs[c];

            //texture coordinates for the character
            float texX1 = glyph.x / (float)fontLoader->GetAtlasWidth(); // width
            float texY1 = glyph.y / (float)fontLoader->GetAtlasHeight(); //height
            float texX2 = (glyph.x + glyph.width) / (float)fontLoader->GetAtlasWidth();
            float texY2 = (glyph.y + glyph.height) / (float)fontLoader->GetAtlasHeight();

            float charWidth = glyph.width;
            float charHeight = glyph.height;

            float xpos = x + offsetX + glyph.bearingX;
            float ypos = y + offsetY + (charHeight - glyph.bearingY);

            float w = glyph.width;   // actual width of the glyph quad
            float h = glyph.height;  // actual height of the glyph quad

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

            unsigned int baseIndex = (textProps.vertices.size() / 4) - 4;
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


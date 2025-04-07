#include "Label.h"

namespace CFrame 
{
	Label::Label(int x, int y, int w, int h, const std::string& text, UIElement* parent)
		:UIElement(x,y,w,h,nullptr)
	{
		CreateTexture(text, w, h);
	}

	Label::~Label()
	{

	}
	void Label::Render(Renderer& renderer)
	{
		if (sdfTexture == nullptr) {
			sdfTexture = new Texture(textTexture, width, height);
		}
	}

	void Label::CreateTexture(const std::string& text, int w, int h)
	{
		if (w == -1 || h == -1) {
			return;
		}
		FontLoader fontloader("C:/Users/eelip/Downloads/arial/ARIAL.TTF");
		fontloader.LoadFont();
		
	    textTexture = new unsigned char[w * h];
		memset(textTexture, 0, w * h);

		int penX = 0, penY = 0;
		for (char c : text) {
			int width, height, xOffset, yOffset;
			unsigned char* glyph = fontloader.GetGlyphBitMap(c, 1.0f, 1.0f, width, height, xOffset, yOffset);

			if (!glyph) continue;

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					int destX = penX + x + xOffset;
					int destY = penY + y + yOffset;

					if (destX >= 0 && destX < w && destY >= 0 && destY < h) {
						textTexture[destY * w + destX] = glyph[y * width + x]; // Copies the pixel in 1d array
					}
				}
			}
			penX += width;
		}
	    
	}
	void Label::OnEvent(CFrameEvent& event)
	{
	}
}


#include "FontLoader.h"
#include "../Log.h"
#include <cstdint> 
#include <algorithm>



namespace CFrame {

	FontLoader::FontLoader(const std::string& fontPath)
		:fontPath(fontPath),  fontSize(48.0f)
	{
		
	}

	FontLoader::~FontLoader()
	{
		
	}

	bool FontLoader::LoadFont()
	{
		if (FT_Init_FreeType(&ft)) 
		{
			CF_CORE_ERROR("Failed to init FreeType!");
			return false;
		}

		if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) 
		{
			CF_CORE_ERROR("Failed to load font!");
			return false;
		}

		FT_Set_Pixel_Sizes(face, 0, fontSize);

		CF_CORE_INFO("Font init OK!");

		const int numChars = 128;
		const int cols     = 16;
		const int rows     = (numChars + cols - 1) / cols;

		int maxW = 0, maxH = 0;

		//Find the biggest glyph
		for (int c = 0; c < numChars; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;

			maxW = std::max(maxW, static_cast<int>(face->glyph->bitmap.width));
			maxH = std::max(maxH, static_cast<int>(face->glyph->bitmap.rows));
		}

		int cellW  = maxW;
		int cellH  = maxH;
		int atlasW = cols * cellW;
		int atlasH = rows * cellH;

		fontBuffer.resize(atlasW * atlasH, 0);

		for (int c = 0; c < numChars; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;

			FT_Bitmap& bmp = face->glyph->bitmap;

			int col = c % cols;
			int row = c / cols;
			int x   = col * cellW;
			int y   = row * cellH;

			//write the glyph to the atlas
			for (int j = 0; j < bmp.rows; j++) {
				for (int i = 0; i < bmp.width; i++) {
					int dstIndex = (y + j) * atlasW + (x + i);
					int srcIndex = j * bmp.pitch + i;
					fontBuffer[dstIndex] = bmp.buffer[srcIndex];
				}
			}
			fontInfo info;
			info.x = x;
			info.y = y;
			info.width    = bmp.width;
			info.height   = bmp.rows;
			info.bearingX = face->glyph->bitmap_left;
			info.bearingY = face->glyph->bitmap_top;
			info.advance = face->glyph->advance.x >> 6;

			glyphs[c] = info;
		}
		return true;
	}

   

	std::vector<uint8_t> FontLoader::GetFontAtlas()
    {
		return fontBuffer;
    }

}

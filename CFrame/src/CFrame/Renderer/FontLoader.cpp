#include "FontLoader.h"
#include "../Log.h"


namespace CFrame {

	FontLoader::FontLoader(const std::string& fontPath)
		:fontPath(fontPath),  fontSize(48.0f)
	{
		
	}

	FontLoader::~FontLoader()
	{
		for (auto& pair : glyphCache) {
			free(pair.second);
		}
		glyphCache.clear();
	}

	bool FontLoader::LoadFont()
	{
		std::ifstream file(fontPath, std::ios::binary);
		if (!file.is_open()) {
			CF_CORE_ERROR("Error opening font file: ");
			return false;
		}

		fontBuffer = std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		
		if (!stbtt_InitFont(&fontInfo, fontBuffer.data(), 0)) {
			CF_CORE_ERROR("Error initializing the font");
			return false;
		}
		return true;
	}

	unsigned char* FontLoader::GetGlyphBitMap(int charCode, float scaleX, float scaleY, int& width, int& height, int& xOffset, int& yOffset)
	{
		if (glyphCache.find(charCode) != glyphCache.end()) {
			return glyphCache[charCode];
		}

		float scale_x = scaleX;
		float scale_y = scaleY;

		int glyphIndex = stbtt_FindGlyphIndex(&fontInfo, charCode);
		unsigned char* bitmap = stbtt_GetGlyphBitmap(&fontInfo, scale_x, scale_y, glyphIndex, &width, &height, &xOffset, &yOffset);

		glyphCache[charCode] = bitmap;

		return bitmap;
	}

}

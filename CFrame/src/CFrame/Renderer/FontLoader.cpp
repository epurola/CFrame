#include "FontLoader.h"
#include "../Log.h"
#include <cstdint> 


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

   

	uint8_t* FontLoader::GetGlyphBitMap(int charCode, float scaleX, float scaleY, int& width, int& height, int& xOffset, int& yOffset)
    {
		if (glyphCache.find(charCode) != glyphCache.end()) {
			return glyphCache[charCode];
		}

		// Compute pixel height scale (this replaces scaleX/scaleY with a proper font size scale)
		float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontSize);  // fontSize should be a member variable
		float finalScaleX = scale * scaleX;
		float finalScaleY = scale * scaleY;

		// Use stbtt_GetCodepointBitmap directly 
		uint8_t* bitmap = stbtt_GetCodepointBitmap(
			&fontInfo,
			finalScaleX,
			finalScaleY,
			charCode,
			&width,
			&height,
			&xOffset,
			&yOffset
		);

		size_t bitmapSize = static_cast<size_t>(width) * static_cast<size_t>(height);
		uint8_t* bitmapCopy = new uint8_t[bitmapSize];
		memcpy(bitmapCopy, bitmap, bitmapSize);
		stbtt_FreeBitmap(bitmap, nullptr);

		glyphCache[charCode] = bitmapCopy;
		return bitmapCopy;
    }

}

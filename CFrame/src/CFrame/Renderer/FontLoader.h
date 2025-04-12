#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <ft2build.h>
#include FT_FREETYPE_H

struct fontInfo {
	int x, y;
	int width, height;
	int bearingX, bearingY;
	int advance;
};

namespace CFrame {

	class FontLoader {

	public:
		FontLoader(const std::string& fontPath);
		~FontLoader();


		bool LoadFont();
		std::vector<uint8_t>     GetFontAtlas();
		std::map<char, fontInfo> GetGlyphs() { return glyphs; }

		int GetAtlasWidth()  const { return atlasWidth; }
		int GetAtlasHeight() const { return atlasHeight; }


	private:
		int atlasWidth, atlasHeight;
		std::string fontPath;
		std::vector<uint8_t> fontBuffer;
		FT_Library ft;
		FT_Face face;
		float fontSize;
		
		std::map<char, fontInfo> glyphs;

	};
}
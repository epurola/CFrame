#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>

extern "C" {
	typedef struct FT_LibraryRec_* FT_Library;
	typedef struct FT_FaceRec_* FT_Face;
}

struct fontInfo {
	int x, y;
	int width, height;
	int bearingX, bearingY;
	int advance;
};

namespace CFrame {

	class FontLoader {

	public:
		FontLoader(const std::string& fontPath, float fontSize);
		~FontLoader();


		bool LoadFont();
		bool LoadIcons();
		std::vector<uint8_t>     GetFontAtlas();
		std::map<char, fontInfo> GetGlyphs() { return glyphs; }

		int GetAtlasWidth()  const { return atlasWidth; }
		int GetAtlasHeight() const { return atlasHeight; }


	private:
		int atlasWidth, atlasHeight;
		std::string fontPath;
		std::vector<uint8_t> fontBuffer;
		FT_Library ft;
		FT_Face iconFace;
		FT_Library ftIcon;
		FT_Face faceIcon;
		float fontSize;
		
		std::map<char, fontInfo> glyphs;

	};
}
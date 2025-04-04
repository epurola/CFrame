#pragma once
#include <stb_truetype.h> // Defined in animator.cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>


namespace CFrame {

	class FontLoader {

	public:
		FontLoader(const std::string& fontPath);
		~FontLoader();


		bool LoadFont();
		unsigned char* GetGlyphBitMap(int charCode, float scaleX, float scaleY, int& width, int& height, int& xOffset, int& yOffset);

	private:
		std::string fontPath;
		std::vector<unsigned char> fontBuffer;
		stbtt_fontinfo fontInfo;
		float fontSize;

		std::unordered_map<int, unsigned char*> glyphCache;

	};
}
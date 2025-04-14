#include "FontManager.h"

namespace CFrame 
{
	std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>>& FontManager::GetFont(FontKey key)
	{

		if (fonts.find(key) == fonts.end()) {
			FontLoader fontLoader("C:/dev/CFrame/CFrame/src/CFrame/res/fonts/arial.ttf", key.fontSize);
			fontLoader.LoadFont();
			std::vector<uint8_t> atlas = fontLoader.GetFontAtlas();
			std::map<char, fontInfo> glyphs = fontLoader.GetGlyphs();

			auto atlasTexture = std::make_shared<Texture>(atlas.data(), fontLoader.GetAtlasWidth(), fontLoader.GetAtlasHeight());

			fonts[key] = std::make_pair(std::move(atlasTexture), std::move(glyphs));
		}
		return fonts[key];
	}

	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{

	}
}


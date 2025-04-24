#include "FontManager.h"

namespace CFrame 
{

	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{

	}

	std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>>& FontManager::GetFont(FontKey key)
	{

		if (fonts.find(key) == fonts.end()) {
			FontLoader fontLoader(GetFontPath(key.font), key.fontSize);
           
            if (key.font != SegoeMDL2Assets) {
                fontLoader.LoadFont();
            }
            else {
                fontLoader.LoadIcons();
            }
            
			std::vector<uint8_t> atlas = fontLoader.GetFontAtlas();
			std::map<char, fontInfo> glyphs = fontLoader.GetGlyphs();

			auto atlasTexture = std::make_shared<Texture>(atlas.data(), fontLoader.GetAtlasWidth(), fontLoader.GetAtlasHeight());

			fonts[key] = std::make_pair(std::move(atlasTexture), std::move(glyphs));
		}
		return fonts[key];
	}

    std::string FontManager::GetFontPath(Font font) {
        switch (font) {
        case Font::Arial:
            return "C:/Windows/Fonts/arial.ttf";
        case Font::ArialBold:
            return "C:/Windows/Fonts/arialbd.ttf";
        case Font::TimesNewRoman:
            return "C:/Windows/Fonts/times.ttf";
        case Font::CourierNew:
            return "C:/Windows/Fonts/cour.ttf";
        case Font::Calibri:
            return "C:/Windows/Fonts/calibri.ttf";
        case Font::Cambria:
            return "C:/Windows/Fonts/cambria.ttc";
        case Font::Consolas:
            return "C:/Windows/Fonts/consola.ttf";
        case Font::SegoeUI:
            return "C:/Windows/Fonts/segoeui.ttf";
        case Font::Tahoma:
            return "C:/Windows/Fonts/tahoma.ttf";
        case Font::Verdana:
            return "C:/Windows/Fonts/verdana.ttf";
        case Font::VerdanaBold:
            return "C:/Windows/Fonts/verdanab.ttf";

            // Icon Fonts
        case Font::SegoeMDL2Assets: // Windows 10/11 icon font. Currently cant load them
            return "C:/Windows/Fonts/segmdl2.ttf";
        case Font::Wingdings:
            return "C:/Windows/Fonts/wingding.ttf";
        case Font::Webdings:
            return "C:/Windows/Fonts/webdings.ttf";

        default:
            return ""; 
        }
    }


}


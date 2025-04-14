#pragma once
#include "FontLoader.h"
#include "Texture.h"
#include <unordered_map>
#include <functional>

namespace CFrame {
	enum Font {
		Arial
	};

	struct FontKey {
		Font font;
		float fontSize;

		bool operator ==(const FontKey& other) const {
			return font == other.font && fontSize == other.fontSize;
		}
	};
}

namespace std {
	template <>
	struct hash<CFrame::FontKey> {
		std::size_t operator()(const CFrame::FontKey& key) const {

			return std::hash<int>()(static_cast<int>(key.font)) ^ (std::hash<float>()(key.fontSize) << 1);
		}

	};
}

namespace CFrame {


	class FontManager {

	public:
		static FontManager& GetInstance() {
			static FontManager instance;
			return instance;
		}

		FontManager(const FontManager&) = delete;
		FontManager& operator=(const FontManager&) = delete;

		std::pair <std::shared_ptr<Texture>, std::map<char, fontInfo>>& GetFont(FontKey key);


	private:
		FontManager();
		~FontManager();
		//Cache to hold loaded fonts with ready made texture atlas and glyph data
		std::unordered_map < FontKey, std::pair<std::shared_ptr<Texture>, std::map<char, fontInfo>>> fonts;


	};
}
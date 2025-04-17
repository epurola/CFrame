#include "Color.h"
#include <SDL3/SDL.h>

// Define static color instances with muted, faded tones
constexpr Color Color::Red{ 204, 68, 51, 255 };
constexpr Color Color::Green{ 77, 182, 128, 255 };
constexpr Color Color::Blue{ 23,37,42, 255 };
constexpr Color Color::Black{ 43, 43, 43, 255 };
constexpr Color Color::White{ 245, 245, 245, 255 };
constexpr Color Color::Yellow{ 204, 204, 102, 255 };
constexpr Color Color::Orange{ 255, 122, 51, 255 };
constexpr Color Color::Pink{ 255, 182, 193, 255 };
constexpr Color Color::Purple{ 130, 98, 155, 255 };
constexpr Color Color::Cyan{ 102, 204, 204, 255 };
constexpr Color Color::Magenta{ 204, 102, 204, 255 };
constexpr Color Color::Gray{ 128, 128, 128, 255 };
constexpr Color Color::LightGray{ 211, 211, 211, 255 };
constexpr Color Color::DarkGray{ 64, 64, 64, 255 };
constexpr Color Color::Brown{ 139, 85, 64, 255 };
constexpr Color Color::Teal{ 64, 128, 128, 255 };
constexpr Color Color::Lime{ 77, 182, 77, 255 };
constexpr Color Color::Navy{ 51, 51, 102, 255 };
constexpr Color Color::Gold{ 204, 174, 51, 255 };
constexpr Color Color::Silver{ 169, 169, 169, 255 };
constexpr Color Color::Maroon{ 102, 0, 0, 255 };
constexpr Color Color::Olive{ 107, 142, 35, 255 };

SDL_Color Color::toSDLColor(float opacity) const
{
    opacity = (opacity < 0.0f) ? 0.0f : (opacity > 1.0f) ? 1.0f : opacity;
    Uint8 alpha = static_cast<Uint8>(opacity * 255);
    return SDL_Color{ r, g, b, alpha };
}

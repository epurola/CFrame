#pragma once
#include <cstdint> 
#include <iostream>
#include "../Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

struct SDL_Color;
struct CFRAME_API Color {
    uint8_t r, g, b, a;

    constexpr Color() : r(0), g(0), b(0), a(0) {}

    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {
    }

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
    static const Color Yellow;
    static const Color Orange;
    static const Color Pink;
    static const Color Purple;
    static const Color Cyan;
    static const Color Magenta;
    static const Color Gray;
    static const Color LightGray;
    static const Color LightGray2;
    static const Color DarkGray;
    static const Color Brown;
    static const Color Teal;
    static const Color Lime;
    static const Color Navy;
    static const Color Gold;
    static const Color Silver;
    static const Color Maroon;
    static const Color Olive;

    SDL_Color toSDLColor(float opacity) const;

    glm::vec4 Color::ToVec4() const;
};
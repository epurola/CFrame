#pragma once
#include <string>
#include <glad/glad.h>
//#include "stb_Image/stb_image.h"

namespace CFrame {


    class Texture
    {
    private:
        unsigned int RendererId;
        std::string filePath;
        unsigned char* localBuffer;
        int width, height, BPP;

    public:
        Texture(const std::string& filePath);
        ~Texture();

        void Bind(unsigned int slot = 0);
        void UnBind();

        inline int getWidth() const { return width; };
        inline int getHeight() const { return height; };
    };

}
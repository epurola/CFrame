#pragma once
#include <string>



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
        Texture(unsigned char* buffer, int width, int height);
        Texture() {};
        ~Texture();

        void Bind(unsigned int slot = 0);
        void UnBind();

        inline int GetWidth()  const { return width; };
        inline int GetHeight() const { return height; };
    };

}
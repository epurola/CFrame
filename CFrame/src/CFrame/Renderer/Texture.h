#pragma once
#include <string>



namespace CFrame {


    class Texture
    {
    private:
        unsigned int RendererId=0;
        std::string filePath = "";
        unsigned char* localBuffer = 0;
        int width = 0;
        int height =0;
        int BPP = 0;

    public:
        Texture(const std::string& filePath);
        Texture(unsigned char* buffer, int width, int height);
       
        ~Texture();

        void Bind(unsigned int slot = 0);
        void UnBind();

        inline int GetWidth()  const { return width; };
        inline int GetHeight() const { return height; };
    };

}
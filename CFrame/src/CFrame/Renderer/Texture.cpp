#include "Texture.h"
#include <iostream>
#include "stb_image.h"

namespace CFrame {

    Texture::Texture(const std::string& filePath)
        : filePath(filePath), localBuffer(nullptr), width(0), height(0), BPP(0),
        RendererId(0)
    {
        stbi_set_flip_vertically_on_load(0);
        localBuffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 4); //4  = desired channels
        if (!localBuffer) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            return;
        }

        glGenTextures(1, &RendererId);
        glBindTexture(GL_TEXTURE_2D, RendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            localBuffer);

        glBindTexture(GL_TEXTURE_2D, 0);

        if (localBuffer) {
            stbi_image_free(localBuffer);
        }
    }

    Texture::Texture(unsigned char* buffer, int width, int height)
        :localBuffer(buffer), width(width), height(height), RendererId(0)
    {
        glGenTextures(1, &RendererId);
        glBindTexture(GL_TEXTURE_2D, RendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            localBuffer);

        glBindTexture(GL_TEXTURE_2D, 0);

    }

    Texture::Texture()
    {

    }

    Texture::~Texture()
    {

        glDeleteTextures(1, &RendererId);
       
    }

    void Texture::Bind(unsigned int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, RendererId);
    }

    void Texture::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}


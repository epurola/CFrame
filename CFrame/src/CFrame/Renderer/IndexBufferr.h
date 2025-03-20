#pragma once
#include <glad/glad.h>
namespace CFrame {

    class IndexBuffer {

    private:
        unsigned int RendererId;
        unsigned int count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return count; }
    };
}
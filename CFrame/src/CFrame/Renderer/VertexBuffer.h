#pragma once
#include <glad/glad.h>

namespace CFrame {

    class VertexBuffer {

    private:
        unsigned int RendererId;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}
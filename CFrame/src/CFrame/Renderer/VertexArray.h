#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"


namespace CFrame {
    class VertexArray
    {
    private:
        unsigned int RendererId;


    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout);
        void Bind() const;
        void UnBind() const;

    };
}
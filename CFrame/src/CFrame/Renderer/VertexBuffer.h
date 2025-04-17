#pragma once


namespace CFrame {

    class VertexBuffer {

    private:
        unsigned int RendererId;
        unsigned int currSize = 0;


    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void SetData(const void* data, unsigned int size);

        void Bind() const;
        void Unbind() const;

    };
}
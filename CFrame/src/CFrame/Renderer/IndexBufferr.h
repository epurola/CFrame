#pragma once

namespace CFrame {

    class IndexBuffer {

    private:
        unsigned int RendererId;
        unsigned int count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void SetData(const unsigned int* data, unsigned int count);
        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return count; }
    };
}
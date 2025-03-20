#pragma once
#include <vector>
#include <glad/glad.h>
namespace CFrame {


    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type) {
            switch (type) {
            case GL_FLOAT:         return 4;
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 1;
            }
            return 0;
        }

        VertexBufferElement(unsigned int type, unsigned int count, bool normalized)
            : type(type), count(count), normalized(normalized) {
        }
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferElement> Elements;
        unsigned int stride;
    public:
        VertexBufferLayout()
            :stride(0) {
        }

        template<typename T>
        void Push(unsigned int count) {
            stattic_assert(false);
        }

        template<>
        void Push<float>(unsigned int count) {
            Elements.push_back({ GL_FLOAT, count, GL_FALSE });
            stride += count * sizeof(GL_FLOAT);
        }

        template<>
        void Push<unsigned int>(unsigned int count) {
            Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
            stride += count * sizeof(GLuint);
        }

        template<>
        void Push<unsigned char>(unsigned int count) {
            Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
            stride += count * sizeof(GLbyte);
        }

        inline const std::vector<VertexBufferElement> Getelements() const { return Elements; };
        inline unsigned int GetStride() const { return stride; };

    };
}

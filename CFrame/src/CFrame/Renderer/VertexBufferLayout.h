#pragma once
#include <vector>

namespace CFrame {
    // Forward-declared GL types for header safety
    typedef unsigned int GLenum;
    typedef unsigned int GLuint;
    typedef unsigned char GLbyte;
    typedef float GLfloat;

    // Constants you'd normally get from glad/gl.h
    constexpr GLenum CF_GL_FLOAT = 0x1406;
    constexpr GLenum CF_GL_UNSIGNED_INT = 0x1405;
    constexpr GLenum CF_GL_UNSIGNED_BYTE = 0x1401;
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type) {
            switch (type) {
            case CF_GL_FLOAT:         return 4;
            case CF_GL_UNSIGNED_INT:  return 4;
            case CF_GL_UNSIGNED_BYTE: return 1;
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
            static_assert(false);
        }

        template<>
        void Push<float>(unsigned int count) {
            Elements.push_back({ CF_GL_FLOAT, count, false });
            stride += count * sizeof(CF_GL_FLOAT);
        }

        template<>
        void Push<unsigned int>(unsigned int count) {
            Elements.push_back({ CF_GL_UNSIGNED_INT, count, false });
            stride += count * sizeof(GLuint);
        }

        template<>
        void Push<unsigned char>(unsigned int count) {
            Elements.push_back({ CF_GL_UNSIGNED_BYTE, count, true });
            stride += count * sizeof(GLbyte);
        }

        inline const std::vector<VertexBufferElement> Getelements() const { return Elements; };
        inline unsigned int GetStride() const { return stride; };

    };
}

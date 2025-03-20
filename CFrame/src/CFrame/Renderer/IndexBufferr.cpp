#include "IndexBufferr.h"

namespace CFrame 
{
    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        :count(count)
    {
        glGenBuffers(1, &RendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &RendererId);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

#include "IndexBufferr.h"
#include <glad/glad.h>

namespace CFrame 
{
    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        :count(count), RendererId(0)
    {
        glGenBuffers(1, &RendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &RendererId);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId);
    }

    void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererId); 
        if (this->count < count) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
        }
        else {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data);
        }
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

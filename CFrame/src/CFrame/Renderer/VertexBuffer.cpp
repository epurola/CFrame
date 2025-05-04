#pragma once

#include "VertexBuffer.h"
#include <glad/glad.h>


namespace CFrame{

    VertexBuffer::VertexBuffer(const void* data, unsigned int size)
        :RendererId(0), currSize(0)
    {
        glGenBuffers(1, &RendererId);
        
        glBindBuffer(GL_ARRAY_BUFFER, RendererId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &RendererId);
    }

    void VertexBuffer::SetData(const void* data, unsigned int size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, RendererId);

        if (currSize < size) {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW); 
            currSize = size;
        }
        else {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, RendererId);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}



#include "VertexArray.h"
#include <glad/glad.h>

namespace CFrame 
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &RendererId);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &RendererId);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(RendererId);
    }

    void VertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout)
    {
        Bind();
        vb.Bind();
        const auto& elements = layout.Getelements();
        unsigned int offset = 0;

        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                element.count,
                element.type,
                element.normalized,
                layout.GetStride(),
                (const void*)(uintptr_t)offset);

            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }

    }
}

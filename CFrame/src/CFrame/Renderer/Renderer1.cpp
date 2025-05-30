#include "Renderer1.h"
#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace CFrame {

	Renderer1::Renderer1(Window& window)
        :window(window)
	{
        shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");
        textShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/textShader.shader");
        lineShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/lineShader.shader");
        screenShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/screenShader.shader");

        FBO = std::make_unique<FrameBuffer>(window.GetWidth(), window.GetHeight());
	}

	Renderer1::~Renderer1()
	{
       
    }

    void Renderer1::Resize(int w, int h)
    {
        FBO->Resize(w, h);
    }

    void Renderer1::AddToBatch(ElementProperties p)
    {
      
    }

    void Renderer1::Flush()
    {
        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();

        if (!VA) {
            VA = std::make_unique<VertexArray>();
            Layout = std::make_unique<VertexBufferLayout>();
            VB = std::make_unique<VertexBuffer>(batchVertices.data(), static_cast<unsigned int>(batchVertices.size() * sizeof(float)));
            Indices = std::make_unique<IndexBuffer>(batchIndices.data(), static_cast<unsigned int>(batchIndices.size()));

            Layout->Push<float>(2); // Position x, y
            Layout->Push<float>(4); // Color Data r, g, b, a
            Layout->Push<float>(2); // Texture coordinates
            Layout->Push<float>(4); // Gradient Color Data r, g, b, a
            VA->AddBuffer(*textVB, *textLayout);
        }

        VA->Bind();
        VB->SetData(batchVertices.data(), static_cast<unsigned int>(batchVertices.size() * sizeof(float)));
        Indices->SetData(batchIndices.data(), static_cast<unsigned int>(batchIndices.size()));

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
            float(windowHeight), 0.0f,  // Bottom, Top
            -1.0f, 1.0f);
    }
    
    void Renderer1::BeginFrame()
    {
        int w = window.GetWidth();
        int h = window.GetHeight();
        FBO->Resize(w, h);  //Will return early if no resize needed
       
        glViewport(0, 0, w, h);
        //Clear the default framebuffer to avoid flicker on window resi
        glClear(GL_COLOR_BUFFER_BIT);
        FBO->Bind();
        glClear(GL_COLOR_BUFFER_BIT);
       
    }

    void Renderer1::EndFrame()
    {
        
       // Flush();
        FBO->Unbind();
        // Draw a full-screen quad with fboTexture bound
        screenShader->Bind();
        FBO->BindTexture();
        DrawFullScreenQuad(); // simple VAO that draws a 2-triangle fullscreen rectangle
    }

    void Renderer1::DrawFullScreenQuad()
    {
        if (!screenVA)
        {
            float quadVertices[] = {
                // positions     // texCoords
                -1.0f,  1.0f,     0.0f, 1.0f, // Top-left     = 0
                -1.0f, -1.0f,     0.0f, 0.0f, // Bottom-left  = 1
                 1.0f, -1.0f,     1.0f, 0.0f, // Bottom-right = 2
                 1.0f,  1.0f,     1.0f, 1.0f  // Top-right    = 3
            };
            screenVA      = std::make_unique<VertexArray>();
            screenLayout  = std::make_unique<VertexBufferLayout>();
            screenVB      = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
            screenIndices = std::make_unique<IndexBuffer>(rectIndecies, 6);
            screenLayout->Push<float>(2);
            screenLayout->Push<float>(2);
            screenVA->AddBuffer(*screenVB, *screenLayout);
        }

        screenVA->Bind();
        screenIndices->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
        

    //ToDo: Remove dependecy on SDL color here
	void Renderer1::DrawRectangle(float x, float y, float w, float h, 
        ElementProperties p, float speed, float time,
        Texture* texture)
	{
        bool hasTexture = false;
        if (texture != nullptr) {
            texture->Bind();
            hasTexture = true;
        }
        else {
           // AddToBatch(p);
            //return;
        }

        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();
        //ClipOverflow(x, y, w, h, windowHeight);

        float r = p.colors.background1.r;
        float g = p.colors.background1.g;
        float b = p.colors.background1.b;
        float a = p.opacity;

        float rg = p.colors.background2.r;
        float gg = p.colors.background2.g;
        float bg = p.colors.background2.b;
        float ag = p.opacity;

        float rb = p.colors.border1.r;
        float gb = p.colors.border1.g;
        float bb = p.colors.border1.b;
        float ab = p.colors.border1.a;

        float rgb = p.colors.border2.r;
        float ggb = p.colors.border2.g;
        float bgb = p.colors.border2.b;
        float agb = p.colors.border2.a;

 
        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,                                        r, g, b, a         texture coordinates      Gradient color
            location = 0                                    location = 1       location = 2             location = 3*/
           p.vertices.topLeft.x , p.vertices.topLeft.y,           r, g, b, a,     0.0f, 1.0f,     rg, gg, bg, ag,     // Top-left
           p.vertices.topRight.x, p.vertices.topRight.y,          r, g, b, a,     1.0f, 1.0f,     rg, gg, bg, ag,     // Top-right
           p.vertices.bottomRight.x , p.vertices.bottomRight.y,   r, g, b, a,     1.0f, 0.0f,     rg, gg, bg, ag,     // Bottom-right
           p.vertices.bottomLeft.x, p.vertices.bottomLeft.y,      r, g, b, a,     0.0f, 0.0f,     rg, gg, bg, ag,  
        };

        /*create vertex buffer with the vertices and the size of the data
        4 vertices with 12 data point that are floats.
        Will also automaticaaly bind it*/
        if (!rectVA) {
            /*Create Vertex Array*/
            rectVA = std::make_unique<VertexArray>();
            rectLayout = std::make_unique<VertexBufferLayout>();
            rectVB = std::make_unique<VertexBuffer>(vertices, static_cast<unsigned int>(4 * 12 * sizeof(float)));
            /*creates index buffer with 6 indecies.*/
            rectIndices = std::make_unique<IndexBuffer>(rectIndecies, 6);
            rectLayout->Push<float>(2); // Position x, y
            rectLayout->Push<float>(4); // Color Data r, g, b, a
            rectLayout->Push<float>(2); // Texture coordinates
            rectLayout->Push<float>(4); // Gradient Color Data r, g, b, a
            rectVA->AddBuffer(*rectVB, *rectLayout);
        }

        rectVA->Bind();
        rectVB->SetData(vertices, 4 * 12 * sizeof(float));
        rectIndices->Bind();

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth),  // Left, Right
                                    float(windowHeight), 0.0f, // Bottom, Top
                                   -1.0f, 1.0f);
      
        //Bind the shader and set uniforms
        shader->Bind();
        shader->SetUniform4f("u_Color", r, g, b, a);
        shader->SetUniform4f("u_Color2", rg, gg, bg, ag);
        shader->SetUniformMat4f("u_MVP", proj);
        shader->SetUniform2f("u_RectMin", x, y);
        shader->SetUniform2f("u_RectMax", x + w, y + h);
        shader->SetUniform1f("u_BottomRight", float(p.radius.bottomRight));
        shader->SetUniform1f("u_BottomLeft", float(p.radius.bottomLeft));
        shader->SetUniform1f("u_TopRight", float(p.radius.topRight));
        shader->SetUniform1f("u_TopLeft", float(p.radius.topLeft));
        shader->SetUniform1f("u_Time", time);
        shader->SetUniform1f("u_Speed", speed);
        shader->SetUniform1f("u_Angle", p.angle);
        shader->SetUniform1f("u_BorderTop", p.border.top);
        shader->SetUniform1f("u_BorderBottom", p.border.bottom);
        shader->SetUniform1f("u_BorderLeft", p.border.left);
        shader->SetUniform1f("u_BorderRight", p.border.right);
        shader->SetUniform4f("u_BorderColor1", rb, gb, bb, ab);
        shader->SetUniform4f("u_BorderColor2", rgb, ggb, bgb, agb);
        shader->SetUniform1i("u_Texture", 0);
        shader->SetUniform1i("u_HasTexture", hasTexture);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}

    void Renderer1::RenderText(float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o)
    {

        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();

        if (!o.overflow) {
            ClipOverflow(o.clipX, o.clipY, o.clipWidth, o.clipHeight, windowHeight);
        }

        if (!textVA) {
            textVA      = std::make_unique<VertexArray>();
            textLayout  = std::make_unique<VertexBufferLayout>();
            textVB      = std::make_unique<VertexBuffer>(t.vertices.data(), static_cast<unsigned int>(t.vertices.size() * sizeof(float)));
            textIndices = std::make_unique<IndexBuffer>(t.indices.data(), static_cast<unsigned int>(t.indices.size()));

            textLayout->Push<float>(2); // Position x, y
            textLayout->Push<float>(2); // Texture coordinates
            textVA->AddBuffer(*textVB, *textLayout);
        }

        textVA->Bind();
        textVB->SetData(t.vertices.data(), static_cast<unsigned int>(t.vertices.size() * sizeof(float)));
        textIndices->SetData(t.indices.data(), static_cast<unsigned int>(t.indices.size()));
        

        if (atlas != nullptr) {
            atlas->Bind();
        }

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
                                   float(windowHeight), 0.0f,  // Bottom, Top
                                                -1.0f, 1.0f); 
        //Todo: Also use the second color
        float r = t.color1.r / 255.0f;
        float g = t.color1.g / 255.0f;
        float b = t.color1.b / 255.0f;
        float a = t.opacity;

        float r2 = t.color2.r / 255.0f;
        float g2 = t.color2.g / 255.0f;
        float b2 = t.color2.b / 255.0f;
        float a2 = t.color2.a / 255.0f;

        textShader->Bind();
        textShader->SetUniform4f("u_Color", r, b, g, a);
        textShader->SetUniform4f("u_Color2", r2, g2, b2, a2);
        textShader->SetUniform1f("u_Speed", 1.0f);
        textShader->SetUniform1f("u_Time", 1.0f);
        textShader->SetUniformMat4f("u_MVP", proj);
        textShader->SetUniform1i("u_Texture", 0); 
        textShader->SetUniform1f("u_Opacity", t.opacity);

        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(t.indices.size()), GL_UNSIGNED_INT, nullptr);

        if (!o.overflow) {
            DisableOverflow();
        }
    }

    void Renderer1::DrawLine(LineProperties p)
    {
        int windowWidth = window.GetWidth();
        int windowHeight = window.GetHeight();

        float r = p.color.r / 255.0f;
        float g = p.color.g / 255.0f;
        float b = p.color.b / 255.0f;
        float a = p.color.a / 255.0f;

        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
           p.vertices.topLeft.x , p.vertices.topLeft.y,           r, g, b, a,    
           p.vertices.topRight.x, p.vertices.topRight.y,          r, g, b, a,    
           p.vertices.bottomRight.x , p.vertices.bottomRight.y,   r, g, b, a,     
           p.vertices.bottomLeft.x, p.vertices.bottomLeft.y,      r, g, b, a    
        };

        if (!lineVA) {
            /*Create Vertex Array*/
            lineVA = std::make_unique<VertexArray>();
            lineLayout = std::make_unique<VertexBufferLayout>();
            lineVB = std::make_unique<VertexBuffer>(vertices, static_cast<unsigned int>(4 * 6 * sizeof(float)));
            /*creates index buffer with 6 indecies.*/
            lineIndices = std::make_unique<IndexBuffer>(rectIndecies, 6);
            lineLayout->Push<float>(2); // Position x, y
            lineLayout->Push<float>(4); // Color Data r, g, b, a
        }

        lineVA->Bind();
        lineVB->SetData(vertices, 4 * 6 * sizeof(float));
        lineVA->AddBuffer(*lineVB, *lineLayout);
        lineIndices->Bind();

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth),  float(windowHeight), 0.0f, -1.0f, 1.0f);

        //Bind the shader and set uniforms
        lineShader->Bind();
        lineShader->SetUniform4f("u_Color", r, g, b, a);
        lineShader->SetUniformMat4f("u_MVP", proj);
       
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer1::ClipOverflow(int x, int y, int width, int height, int windowHeight)
    {
        int flippedY = windowHeight - y - height;
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, flippedY, width, height);
    }

    void Renderer1::DisableOverflow()
    {
        glDisable(GL_SCISSOR_TEST);
    }

}


#include "Renderer.h"
#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#define M_PI 3.14159265358979323846


namespace CFrame {

	Renderer::Renderer(Window& window)
        :window(window)
	{
        shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");

        textShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/textShader.shader");
	}

	Renderer::~Renderer()
	{
       
    }
        

    //ToDo: Remove dependecy on SDL color here
	void Renderer::DrawRectangle(float x, float y, float w, float h, 
        ElementProperties p, float speed, float time,
        Texture* texture)
	{
        bool hasTexture = false;
        if (texture != nullptr) {
            texture->Bind();
            hasTexture = true;
        }
       
        SDL_Color c = p.color1.toSDLColor(p.opacity);
        SDL_Color c1 = p.color1.toSDLColor(p.opacity);

        float r = c.r / 255.0f;
        float g = c.g / 255.0f;
        float b = c.b / 255.0f;
        float a = c.a / 255.0f;

        float rg = c1.r / 255.0f;
        float gg = c1.g / 255.0f;
        float bg = c1.b / 255.0f;
        float ag = c1.a / 255.0f;

        float rb = p.borderColor1.r / 255.0f;
        float gb = p.borderColor1.g / 255.0f;
        float bb = p.borderColor1.b / 255.0f;
        float ab = p.borderColor1.a / 255.0f;

        float rgb = p.borderColor2.r / 255.0f;
        float ggb = p.borderColor2.g / 255.0f;
        float bgb = p.borderColor2.b / 255.0f;
        float agb = p.borderColor2.a / 255.0f;

        int windowWidth  = window.GetWidth();
        int windowHeight = window.GetHeight();

 
        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,                                        r, g, b, a         texture coordinates      Gradient color
            location = 0                                    location = 1       location = 2             location = 3*/
           p.vertices.topLeftX , p.vertices.topLeftY,           r, g, b, a,     0.0f, 1.0f,     rg, gg, bg, ag,     // Top-left
           p.vertices.topRightX, p.vertices.topRightY,          r, g, b, a,     1.0f, 1.0f,     rg, gg, bg, ag,     // Top-right
           p.vertices.bottomRightX , p.vertices.bottomRightY,   r, g, b, a,     1.0f, 0.0f,     rg, gg, bg, ag,     // Bottom-right
           p.vertices.bottomLeftX, p.vertices.bottomLeftY,      r, g, b, a,     0.0f, 0.0f,     rg, gg, bg, ag,  
        };

           
        /*Indecies to draw a rectangle*/
        unsigned int indecies[] = { 0, 1, 2, 2, 3, 0 };

        /*create vertex buffer with the vertices and the size of the data
        4 vertices with 12 data point that are floats.
        Will also automaticaaly bind it*/
        if (!rectVA) {
            /*Create Vertex Array*/
            rectVA = std::make_unique<VertexArray>();
            rectLayout = std::make_unique<VertexBufferLayout>();
            rectVB = std::make_unique<VertexBuffer>(vertices, static_cast<unsigned int>(4 * 12 * sizeof(float)));
            /*creates index buffer with 6 indecies.*/
            rectIndices = std::make_unique<IndexBuffer>(indecies, 6);
            rectLayout->Push<float>(2); // Position x, y
            rectLayout->Push<float>(4); // Color Data r, g, b, a
            rectLayout->Push<float>(2); // Texture coordinates
            rectLayout->Push<float>(4); // Gradient Color Data r, g, b, a
        }

        rectVA->Bind();
        rectVB->SetData(vertices, 4 * 12 * sizeof(float));
        rectVA->AddBuffer(*rectVB, *rectLayout);
        rectIndices->Bind();

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth),  // Left, Right
                                    float(windowHeight), 0.0f, // Bottom, Top
                                   -1.0f, 1.0f);
        
        
        //Bind the shader and set uniforms
        shader->Bind();
        shader->SetUniform1f("u_ZIndex", p.zIndex);
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
        //shader->SetUniform1f("u_Angle", p.angle);
        //shader->SetUniform2f("u_Center", centerX, centerY);
        shader->SetUniform1f("u_BorderTop", p.borderTop);
        shader->SetUniform1f("u_BorderBottom", p.borderBottom);
        shader->SetUniform1f("u_BorderLeft", p.borderLeft);
        shader->SetUniform1f("u_BorderRight", p.borderRight);
        shader->SetUniform4f("u_BorderColor1", rb, gb, bb, ab);
        shader->SetUniform4f("u_BorderColor2", rgb, ggb, bgb, agb);
        shader->SetUniform1i("u_Texture", 0);
        shader->SetUniform1i("u_HasTexture", hasTexture);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        texture->UnBind();

	}

    void Renderer::RenderText(const std::string& text, float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o)
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
        }

        textVA->Bind();
        textVB->SetData(t.vertices.data(), static_cast<unsigned int>(t.vertices.size() * sizeof(float)));
        textIndices->SetData(t.indices.data(), static_cast<unsigned int>(t.indices.size()));
        textVA->AddBuffer(*textVB, *textLayout);

        if (atlas != nullptr) {
            atlas->Bind();
        }

        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
                                   float(windowHeight), 0.0f,  // Bottom, Top
                                                -1.0f, 1.0f); 

        textShader->Bind();
        textShader->SetUniformMat4f("u_MVP", proj);
        textShader->SetUniform1i("u_Texture", 0); 
        textShader->SetUniform1f("u_Opacity", t.opacity);

        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(t.indices.size()), GL_UNSIGNED_INT, nullptr);

        atlas->UnBind();

        if (!o.overflow) {
            DisableOverflow();
        }
    }

    void Renderer::ClipOverflow(int x, int y, int width, int height, int windowHeight)
    {
        int flippedY = windowHeight - y - height;
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, flippedY, width, height);
    }

    void Renderer::DisableOverflow()
    {
        glDisable(GL_SCISSOR_TEST);
    }

}


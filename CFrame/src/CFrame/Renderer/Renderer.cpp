#include "Renderer.h"
#include <iostream>
#include <filesystem>



namespace CFrame {

	Renderer::Renderer(Window& window)
        :window(window)
	{
        shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");
        FontLoader fontloader("C:/Users/eelip/Downloads/arial/ARIAL.TTF");
        fontloader.LoadFont();
        glyph = fontloader.GetGlyphBitMap('A', 1.0f, 1.0f, width, height, xOffset, yOffset);
        CF_CORE_INFO("Width: {0}", width);
        if (glyph) {
            glGenTextures(1, &glyphTexture);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, glyphTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, glyph);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
        }
	}

	Renderer::~Renderer()
	{

	}

    //ToDo: Remove dependecy on SDL color here
	void Renderer::DrawRectangle(float x, float y, float w, float h, 
        SDL_Color color,SDL_Color gradient, float angle, Radius radius, 
        float time, float speed, float border, SDL_Color borderColor, SDL_Color borderGradient)
	{
        float r = color.r / 255.0f;
        float g = color.g / 255.0f;
        float b = color.b / 255.0f;
        float a = color.a / 255.0f;

        float rg = gradient.r / 255.0f;
        float gg = gradient.g / 255.0f;
        float bg = gradient.b / 255.0f;
        float ag = gradient.a / 255.0f;

        float rb = borderColor.r / 255.0f;
        float gb = borderColor.g / 255.0f;
        float bb = borderColor.b / 255.0f;
        float ab = borderColor.a / 255.0f;

        float rgb = borderGradient.r / 255.0f;
        float ggb = borderGradient.g / 255.0f;
        float bgb = borderGradient.b / 255.0f;
        float agb = borderGradient.a / 255.0f;

        int windowWidth, windowHeight; //Todo: Not here
        SDL_GetWindowSize(window.GetWindow(), &windowWidth, &windowHeight);
        

        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,        r, g, b, a         texture coordinates      Gradient color
            location = 0    location = 1       location = 2             location = 3*/
            x, y + h,           r, g, b, a,        0.0f, 1.0f,          rg, gg, bg, ag,        // Top-left
            x + w, y + h,       r, g, b, a,        1.0f, 1.0f,          rg, gg, bg, ag,       // Top-right
            x + w, y ,          r, g, b, a,        1.0f, 0.0f,          rg, gg, bg, ag,       // Bottom-right
            x, y ,              r, g, b, a,        0.0f, 0.0f,          rg, gg, bg, ag
        };

        /*Indecies to draw a rectangle*/
        unsigned int indecies[] = { 0, 1, 2, 2, 3, 0 };

        /*create vertex buffer with the vertices and the size of the data
        4 vertices with 6 data point that are floats.
        Will also automaticaaly bind it*/
        VertexBuffer vb(vertices, 4 * 12 * sizeof(float));

        /*Create Vertex Array*/
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2); // Position x, y
        layout.Push<float>(4); // Color Data r, g, b, a
        layout.Push<float>(2); // Texture coordinates
        layout.Push<float>(4); // Gradient Color Data r, g, b, a
        va.AddBuffer(vb, layout);

        /*creates index buffer with 6 indecies.*/
        IndexBuffer ib(indecies, 6);

        /*Define ortho protection matrix*/
        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
                                    float(windowHeight), 0.0f, // Bottom, Top
                                     -1.0f, 1.0f); // Near, Far
        float zIndex = 0;
        //Bind the shader and set uniforms
        shader->Bind();
        shader->SetUniform1f("u_ZIndex", zIndex);
        shader->SetUniform4f("u_Color", r, g, b, a);
        shader->SetUniform4f("u_Color2", rg, gg, bg, ag);
        shader->SetUniformMat4f("u_MVP", proj);
        shader->SetUniform2f("u_RectMin", x, y);  
        shader->SetUniform2f("u_RectMax", x + w, y + h);      
        shader->SetUniform1f("u_BottomRight", float(radius.bottomRight));
        shader->SetUniform1f("u_BottomLeft", float(radius.bottomLeft));
        shader->SetUniform1f("u_TopRight", float(radius.topRight));
        shader->SetUniform1f("u_TopLeft", float(radius.topLeft));
        shader->SetUniform1f("u_Time", time);
        shader->SetUniform1f("u_Speed", speed);
        //shader->SetUniform1f("u_Angle", angle);
        //shader->SetUniform2f("u_Center", centerX, centerY);
        shader->SetUniform1f("u_BorderThickness", border); // This is currently drawn inside the shape
        shader->SetUniform4f("u_BorderColor1", rb, gb, bb, ab);
        shader->SetUniform4f("u_BorderColor2", rgb, ggb, bgb, agb);
        shader->SetUniform1i("u_Texture", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        va.UnBind();
        vb.Unbind();
        shader->UnBind();
	}

    void Renderer::DrawTexture(float x, float y, float w, float h)
    {
        float vertices[] = {
            /* x, y,           texture coordinates     
            location = 0       location = 2     */       
            x, y + h,              0.0f, 1.0f,              // Top-left
            x + w, y + h,          1.0f, 1.0f,              // Top-right
            x + w, y ,             1.0f, 0.0f,           // Bottom-right
            x, y ,                 0.0f, 0.0f,        
        };

        unsigned int indecies[] = { 0, 1, 2, 2, 3, 0 };

        VertexBuffer vb(vertices, 4 * 12 * sizeof(float));
        IndexBuffer ib(indecies, 6);

        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2); // Position x, y
        layout.Push<float>(2); // Texture coordinates
      
        va.AddBuffer(vb, layout);

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window.GetWindow(), &windowWidth, &windowHeight);
        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
            float(windowHeight), 0.0f, // Bottom, Top
            -1.0f, 1.0f); // Near, Far

        shader->SetUniform1i("u_Texture", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    }
    
}


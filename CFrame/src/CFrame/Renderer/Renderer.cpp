#include "Renderer.h"
#include <iostream>
#include <filesystem>


namespace CFrame {

	Renderer::Renderer(Window& window)
        :window(window)
	{
        shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");
	}

	Renderer::~Renderer()
	{

	}

    //ToDo: Remove dependecy on SDL color here
	void Renderer::DrawRectangle(float x, float y, float w, float h, 
        SDL_Color color,SDL_Color gradient, float angle, int radius, 
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

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window.GetWindow(), &windowWidth, &windowHeight);
        

        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,        r, g, b, a         texture coordinates      Gradient color
            location = 0    location = 1       location = 2             location = 3*/
            x, y + h,           r, g, b, a,        0.0f, 0.0f,          rg, gg, bg, ag,        // Top-left
            x + w, y + h,       r, g, b, a,        1.0f, 0.0f,          rg, gg, bg, ag,       // Top-right
            x + w, y ,          r, g, b, a,        1.0f, 1.0f,          rg, gg, bg, ag,       // Bottom-right
            x, y ,              r, g, b, a,        0.0f, 1.0f,          rg, gg, bg, ag
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
        //Bind the shader and set uniforms
        shader->Bind();
        shader->SetUniform4f("u_Color", r, g, b, a);
        shader->SetUniform4f("u_Color2", rg, gg, bg, ag);
        shader->SetUniformMat4f("u_MVP", proj);
        shader->SetUniform2f("u_RectMin", x, y);  
        shader->SetUniform2f("u_RectMax", x + w, y + h);      
        shader->SetUniform1f("u_Radius", float(radius));
        shader->SetUniform1f("u_Time", time);
        shader->SetUniform1f("u_Speed", speed);
        shader->SetUniform1f("u_BorderThickness", border); // This is currently drawn inside the shape
        shader->SetUniform4f("u_BorderColor1", rb, gb, bb, ab);
        shader->SetUniform4f("u_BorderColor2", rgb, ggb, bgb, agb);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        va.UnBind();
        vb.Unbind();
        shader->UnBind();
	}
}


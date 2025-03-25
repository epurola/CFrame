#include "Renderer.h"
#include <iostream>
#include <filesystem>


namespace CFrame {

	Renderer::Renderer(Window& window)
        :window(window)
	{
       
	}

	Renderer::~Renderer()
	{

	}
	void Renderer::DrawRectangle(float x, float y, float w, float h, SDL_Color color, float angle, int radius)
	{
        float r = color.r / 255.0f;
        float g = color.g / 255.0f;
        float b = color.b / 255.0f;
        float a = color.a / 255.0f;

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window.GetWindow(), &windowWidth, &windowHeight);
        

        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,        r, g, b, a         texture coordinates
            location = 0    location = 1       location = 2*/
            x, y + h,           r, g, b, a,        0.0f, 0.0f,       // Top-left
            x + w, y + h,       r, g, b, a,        1.0f, 0.0f,       // Top-right
            x + w, y ,          r, g, b, a,        1.0f, 1.0f,       // Bottom-right
            x, y ,              r, g, b, a,        0.0f, 1.0f
        };

        /*Indecies to draw a rectangle*/
        unsigned int indecies[] = { 0, 1, 2, 2, 3, 0 };

        /*create vertex buffer with the vertices and the size of the data
        4 vertices with 6 data point that are floats.
        Will also automaticaaly bind it*/
        VertexBuffer vb(vertices, 4 * 8 * sizeof(float));

        /*Create Vertex Array*/
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2); // Position x, y
        layout.Push<float>(4); // Color Data r, g, b, a
        layout.Push<float>(2); // Texture coordinates
        va.AddBuffer(vb, layout);

        /*creates index buffer with 6 indecies.*/
        IndexBuffer ib(indecies, 6);

        /*Define ortho protection matrix*/
        glm::mat4 proj = glm::ortho(0.0f, float(windowWidth), // Left, Right
            float(windowHeight), 0.0f, // Bottom, Top
            -1.0f, 1.0f); // Near, Far

        //create shader with uniform u_Color
        //Shader shader("../../res/shaders/basic.shader");
        Shader shader("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");

        shader.Bind();
        shader.SetUniform4f("u_Color", r, g, b, a);
        shader.SetUniformMat4f("u_MVP", proj);

        shader.SetUniform2f("u_RectMin", x, y);  
        shader.SetUniform2f("u_RectMax", x + w, y + h);      
        shader.SetUniform1f("u_Radius", float(radius));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        va.UnBind();
        vb.Unbind();
        shader.UnBind();
	}
}


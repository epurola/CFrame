#include "Renderer.h"
#include <iostream>
#include <filesystem>
#include "FontLoader.h"




namespace CFrame {

	Renderer::Renderer(Window& window)
        :window(window)
	{
        shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");

        FontLoader fontLoader("C:/dev/CFrame/CFrame/src/CFrame/res/fonts/arial.ttf");
        fontLoader.LoadFont();
	}

	Renderer::~Renderer()
	{

	}

    //ToDo: Remove dependecy on SDL color here
	void Renderer::DrawRectangle(float x, float y, float w, float h, 
        ElementProperties p, float speed, float time,
        Texture* texture)
	{
        if (texture != nullptr) {
            texture->Bind();
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

        int windowWidth, windowHeight; //Todo: Not here
        SDL_GetWindowSize(window.GetWindow(), &windowWidth, &windowHeight);
        
        float ro = p.borderRight;
        float l = p.borderLeft;
        float u = p.borderTop;
        float bo = p.borderBottom;

        /*Vertices of the rectangle. Calculates the top left as the origin*/
        float vertices[] = {
            /* x, y,        r, g, b, a         texture coordinates      Gradient color
            location = 0    location = 1       location = 2             location = 3*/
           x , y + h ,       r, g, b, a,        0.0f, 1.0f,          rg, gg, bg, ag,        // Top-left
           x + w, y + h,     r, g, b, a,        1.0f, 1.0f,          rg, gg, bg, ag,       // Top-right
           x + w , y ,       r, g, b, a,        1.0f, 0.0f,          rg, gg, bg, ag,       // Bottom-right
           x, y,             r, g, b, a,        0.0f, 0.0f,          rg, gg, bg, ag
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
        //shader->SetUniform1f("u_Angle", angle);
        //shader->SetUniform2f("u_Center", centerX, centerY);
        //shader->SetUniform1f("u_BorderThickness", p.border ); // This is currently drawn inside the shape
        shader->SetUniform1f("u_BorderTop", p.borderTop);
        shader->SetUniform1f("u_BorderBottom", p.borderBottom);
        shader->SetUniform1f("u_BorderLeft", p.borderLeft);
        shader->SetUniform1f("u_BorderRight", p.borderRight);
        shader->SetUniform4f("u_BorderColor1", rb, gb, bb, ab);
        shader->SetUniform4f("u_BorderColor2", rgb, ggb, bgb, agb);
        shader->SetUniform1i("u_Texture", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        va.UnBind();
        vb.Unbind();
        shader->UnBind();
        texture->UnBind();
	}

 
    
}


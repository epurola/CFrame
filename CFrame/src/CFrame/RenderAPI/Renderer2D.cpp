#include "Renderer2D.h"
#include "Renderer2D.h"
#include "Renderer2D.h"

namespace CFrame 
{

	Camera2D* Renderer2D::s_Camera = nullptr;
	std::unique_ptr<VertexArray> Renderer2D::VA;
	std::unique_ptr<VertexBuffer> Renderer2D::VB;
	std::unique_ptr<VertexBuffer> Renderer2D::instanceBuffer;
	std::unique_ptr<IndexBuffer> Renderer2D::IB;
	std::unique_ptr<FrameBuffer> Renderer2D::FB;
	std::unique_ptr<Shader> Renderer2D::quadShader;
	std::vector<QuadInstance> Renderer2D::quadInstances;

	std::vector<TextInstance> Renderer2D::text;
	std::unique_ptr<Shader> Renderer2D::textShader;
	std::unique_ptr<VertexArray> Renderer2D::textVA;
	std::unique_ptr<VertexBuffer> Renderer2D::textVB;
	std::unique_ptr<VertexBufferLayout> Renderer2D::textLayout;
	std::unique_ptr<IndexBuffer> Renderer2D::textIndices;

	std::vector<QuadInstanceT> Renderer2D::texturedQuads;
	std::unique_ptr<Shader> Renderer2D::shader;
	std::unique_ptr<VertexArray> Renderer2D::rectVA;
	std::unique_ptr<VertexBuffer> Renderer2D::rectVB;
	std::unique_ptr<VertexBufferLayout> Renderer2D::rectLayout;
	std::unique_ptr<IndexBuffer> Renderer2D::rectIndices;

	void Renderer2D::Init(Camera2D& camera)
	{

		quadShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/Instance.shader");
		textShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/textShader.shader");
		shader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/basic.shader");

		s_Camera = &camera;

		QuadVertex quadVertices[4] = {
		{{-0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,  0.5f}, {1.0f, 1.0f}},
		{{-0.5f,  0.5f}, {0.0f, 1.0f}},
		};

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		VA = std::make_unique<VertexArray>();
		VB = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
		instanceBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(QuadInstance) * 1000);
		IB = std::make_unique<IndexBuffer>(indices, 6);
		FB = std::make_unique<FrameBuffer>(camera.GetWidth(), camera.GetHeight());

		VertexBufferLayout layout;
		layout.Push<float>(2); //pos
		layout.Push<float>(2); //texCoords
		VA->AddBuffer(*VB, layout, false, 0);

		VertexBufferLayout instanceLayout;
		instanceLayout.Push<float>(2);  // position
		instanceLayout.Push<float>(2);  // size
		instanceLayout.Push<float>(4);  // color1 (primary color)
		instanceLayout.Push<float>(4);  // color2 (gradient color)
		instanceLayout.Push<float>(4);  // borderColor1 (border gradient start)
		instanceLayout.Push<float>(4);  // borderColor2 (border gradient end)
		instanceLayout.Push<float>(4);  // borderSizes (top, right, bottom, left)
		instanceLayout.Push<float>(4);  // radius (topLeft, topRight, bottomRight, bottomLeft)
		instanceLayout.Push<float>(1);  // time
		instanceLayout.Push<float>(1);  // speed
		instanceLayout.Push<float>(1);  // angle

		VA->AddBuffer(*instanceBuffer, instanceLayout, true, 2);
	}

	void Renderer2D::Begin()
	{
		text.clear();
		quadInstances.clear();
		texturedQuads.clear();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer2D::End()
	{
		Flush();
	}

	void Renderer2D::DrawQuad(QuadInstance instance)
	{
		quadInstances.push_back(instance);

		if (quadInstances.size() >= 1000)
			Flush();
	}

	void Renderer2D::DrawTex(TextInstance t)
	{
		text.push_back(t);
	}

	void Renderer2D::DrawTextured(QuadInstanceT i)
	{
		texturedQuads.push_back(i);
	}
	
	void Renderer2D::Flush()
	{
		if (quadInstances.empty()) return;

		VA->Bind();
	    IB->Bind();
		instanceBuffer->Bind();
		VB->Bind();
		quadShader->Bind();
		
		quadShader->SetUniformMat4f("u_ViewProjection", s_Camera->GetViewProjection());

		instanceBuffer->SetData(quadInstances.data(), quadInstances.size() * sizeof(QuadInstance));

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, quadInstances.size());

		for (auto& quad : texturedQuads) {
			DrawRectangle(quad.position.x, quad.position.y, quad.size.x, quad.size.y, quad.p, quad.speed, quad.time, quad.texture);
		}
		
		for (auto& t : text) {
			RenderText(t.x, t.y, t.props, t. atlas, t.overflow );
		}

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
	}

	void Renderer2D::RenderText(float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o)
	{

		float windowWidth = s_Camera->GetWidth();
		float windowHeight = s_Camera->GetHeight();

		if (!o.overflow) {
			ClipOverflow(o.clipX, o.clipY, o.clipWidth, o.clipHeight, windowHeight);
		}

		if (!textVA) {
			textVA = std::make_unique<VertexArray>();
			textLayout = std::make_unique<VertexBufferLayout>();
			textVB = std::make_unique<VertexBuffer>(t.vertices.data(), static_cast<unsigned int>(t.vertices.size() * sizeof(float)));
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

	void Renderer2D::DrawRectangle(float x, float y, float w, float h,
		ElementProperties p, float speed, float time,
		Texture* texture)
	{
		bool hasTexture;
		
		texture->Bind();
		hasTexture = true;
		
		float windowWidth = s_Camera->GetWidth();
		float windowHeight = s_Camera->GetHeight();
		//ClipOverflow(x, y, w, h, windowHeight);

		float r = p.colors.background1.r;
		float g = p.colors.background1.g;
		float b = p.colors.background1.b;
		float a = p.opacity;

		float rg = p.colors.background2.r;
		float gg = p.colors.background2.g;
		float bg = p.colors.background2.b;
		float ag = p.opacity;

		float rb = p.colors.border1.r ;
		float gb = p.colors.border1.g ;
		float bb = p.colors.border1.b ;
		float ab = p.colors.border1.a ;

		float rgb = p.colors.border2.r ;
		float ggb = p.colors.border2.g ;
		float bgb = p.colors.border2.b ;
		float agb = p.colors.border2.a ;


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
			rectLayout->Push<float>(2); // Position x, y
			rectLayout->Push<float>(4); // Color Data r, g, b, a
			rectLayout->Push<float>(2); // Texture coordinates
			rectLayout->Push<float>(4); // Gradient Color Data r, g, b, a
			rectVA->AddBuffer(*rectVB, *rectLayout);
		}

		rectVA->Bind();
		rectVB->SetData(vertices, 4 * 12 * sizeof(float));
		IB->Bind();

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

	void Renderer2D::ClipOverflow(int x, int y, int width, int height, int windowHeight)
	{
		int flippedY = windowHeight - y - height;
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, flippedY, width, height);
	}

	void Renderer2D::DisableOverflow()
	{
		glDisable(GL_SCISSOR_TEST);
	}

}


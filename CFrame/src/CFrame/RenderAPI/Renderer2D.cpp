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

	void Renderer2D::Init(Camera2D& camera)
	{

		quadShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/Instance.shader");
		textShader = std::make_unique<Shader>("C:/dev/CFrame/CFrame/src/CFrame/res/shaders/textShader.shader");

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

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
		
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, quadInstances.size());

		quadInstances.clear();

		for (auto& t : text) {
			RenderText(t.x, t.y, t.props, t. atlas, t.overflow );
		}
		
	}
	void Renderer2D::RenderText(float x, float y, TextProperties t, Texture* atlas, OverFlowProperties o)
	{

		float windowWidth = s_Camera->GetWidth();
		float windowHeight = s_Camera->GetHeight();

		if (!o.overflow) {
			//ClipOverflow(o.clipX, o.clipY, o.clipWidth, o.clipHeight, windowHeight);
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
			//DisableOverflow();
		}
	}
}


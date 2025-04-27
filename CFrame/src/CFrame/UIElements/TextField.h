#pragma once
#include "UIelement.h"
#include <variant>
#include <Windows.h>

namespace CFrame {

	class TextField : public UIElement 
	{
	public:
		TextField(int x, int y, int w, int h, UIElement* parent = nullptr);
		~TextField();

		void Render(Renderer& renderer) override;
		void OnEvent(CFrameEvent& event) override;
		void UpdateChildSizes() override;
		void SetIsActive(bool b);
		void RegisterAnimator(std::shared_ptr<ApplicationManager> manager);

		void SetInput(const std::string& value);
		std::string GetInput() const { return input; };
		void UpdateVertexY(int offset);

		bool IsActive() const { return isActive; }

		inline ElementType GetElementType() const override { return ElementType::INPUTFIELD; };


	private:
		std::string input = "";
		int textWidth;
		bool isActive = false;
		std::shared_ptr<Texture> labelTexture;
		std::map<char, fontInfo> glyphs;
		LineProperties lineProperties;
		int offsetOldChar = 0;
		float elapsedTime = 0.0f;
		int cursorHeight;
	};
}
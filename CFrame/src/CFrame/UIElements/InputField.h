#pragma once
#include "UIelement.h"
#include <variant>

namespace CFrame {

	class InputField : public UIElement 
	{
	public:
		InputField(int x, int y, int w, int h, UIElement* parent = nullptr);
		~InputField();

		void Render(Renderer& renderer) override;
		void OnEvent(CFrameEvent& event) override;
		void UpdateChildSizes() override;
		void SetIsActive(bool b);
		void RegisterAnimator(std::shared_ptr<AnimationManager> manager);

		void SetInput(const std::string& value);
		std::string GetInput() const { return input; };

		bool IsActive() const { return isActive; }

		inline ElementType GetElementType() const override { return ElementType::INPUTFIELD; };


	private:
		std::string input = "Hello";
		bool isActive = false;
		std::shared_ptr<Texture> labelTexture;
		std::map<char, fontInfo> glyphs;
	};
}
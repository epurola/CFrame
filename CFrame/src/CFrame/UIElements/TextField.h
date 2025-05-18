#pragma once
#include "UIelement.h"
#include <variant>
#include <Windows.h>
#include "../CFrameEvent/KeyCode.h"

namespace CFrame {

	struct Character {
		char character;  
		int x;            // Left x pos
		int advance;      // how much to move for the next character
		bool selected;    
		bool visible;
	};

	class TextField : public UIElement 
	{
	public:
		TextField(int x, int y, int w, int h, UIElement* parent = nullptr);
		~TextField();

		void OnEvent(CFrameEvent& event) override;
		void Render(Renderer1& renderer) override;
		void Render(float timestep) override;
		void SetInput(const std::string& value);
		void UpdateChildSizes() override;

		void SetFontSize(float size);
		void SetIsActive(bool b);
		
		bool IsActive() const { return isActive; }

		inline ElementType GetElementType() const override { return ElementType::INPUTFIELD; };
		std::string GetInput() const { return input; };


	private:
		std::shared_ptr<Texture> atlasTexture;
		std::vector<Character> characters; //Data to enable editing the text
		std::map<char, fontInfo> glyphs;
		std::string input = "";
		
		LineProperties lineProperties;

		int offsetOldChar = 0;
		int cursorHeight;
		int lineSpacing   = 5;
		int lineNumber    = 0;
		int currIndex     = 0; // For editing and determin which char to edit
		int textWidth     = 0;

		float elapsedTime = 0.0f;
		float offsetX     = 0.0f;
	    float offsetY     = 0.0f;
		float atlasWidth  = 0.0f;
		float atlasHeight = 0.0f;

		bool horizontalScroll = true;
		bool verticalScroll   = false;
		bool isActive         = false;
		
	private:
		bool HandleMouseButtonDown(MouseButtonDownEvent& e);
		bool HandleMouseScroll(MouseScrolledEvent& e);
		bool HandleKeyPressed(KeyPressedEvent& e);
		bool HandleTextInput(TextInputEvent& e);

		void RegisterAnimator(std::shared_ptr<ApplicationManager> manager);
		void AccumulateCursorPosition(int offset);
		void UpdateCursorPosition(int offset);
		void AddCharacter(char c, int index);
		void UpdateVertexY(int offset);
		void UpdateVertexX(int offset);
		void InitializeAtlas();
		void UpdateTextProperties();
		void SetOverFlowProperties();

		int GetCharacterIndex(int cursorX);
	};
}
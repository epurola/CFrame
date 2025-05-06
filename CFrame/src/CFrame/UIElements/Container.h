#pragma once
#include "UIElement.h"
#include "../Renderer/Renderer.h"



namespace CFrame {

	enum class FlexDirection { Row, Column };
	enum class JustifyContent { Start, Center, End, SpaceBetween, SpaceAround, SpaceEvenly };
	enum class AlignItems { Start, Center, End, Stretch };

	class CFRAME_API Container : public UIElement
	{
	public:
		Container(int x, int y, int w, int h, UIElement* parent = nullptr);
		virtual ~Container();
		void SetSpacing(int spacing);
		virtual void UpdateChildSizes() = 0;
		void AddChild(UIElement* child);

		void Render(Renderer& renderer) override;
		void OnEvent(CFrameEvent& event) override;
		void RegisterAnimator(std::shared_ptr<ApplicationManager> manager) override;

		void ToFront(UIElement* child);
		void ToBack(UIElement* child);

		void SetAlignment(AlignItems xAlign, AlignItems yAlign );
		void SetScrollEnabled(bool b);
		void SetIsDirty(bool b) override;

		inline int GetSpacing() const { return spacing; }
		inline ElementType GetElementType() const override { return ElementType::CONTAINER; };
		std::vector<UIElement*> children;
		std::vector<UIElement*> renderChildren;

	protected:
		int spacing = 0;
		AlignItems xAlign, yAlign;
		bool scrollEnabled = false;

	private:
		bool HandleMouseDrag(MouseDraggedEvent& e);
		bool HandleMouseScroll(MouseScrolledEvent& e);
		
	};

}
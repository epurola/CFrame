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
		Container(int x, int y, int w, int h, UIElement* parent);
		virtual ~Container();
		void SetSpacing(int spacing);
		virtual void UpdateChildSizes() = 0;
		void AddChild(UIElement* child);

		void Render(Renderer& renderer) override;

		void SetAlignment(AlignItems xAlign, AlignItems yAlign );
		void SetDragToResize(bool b);

		inline int GetSpacing() const { return spacing; }
		inline ElementType GetElementType() const override { return ElementType::CONTAINER; };
		std::vector<UIElement*> children;

	protected:
		int spacing = 0;
		bool dragToResize;
		AlignItems xAlign, yAlign;
	};

}
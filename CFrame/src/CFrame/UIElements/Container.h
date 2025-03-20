#pragma once
#include "UIElement.h"

namespace CFrame {

	enum class FlexDirection { Row, Column };
	enum class JustifyContent { Start, Center, End, SpaceBetween, SpaceAround, SpaceEvenly };
	enum class AlignItems { Start, Center, End, Stretch };

	class CFRAME_API Container : public UIElement
	{
	public:
		virtual ~Container();
		void SetSpacing(int spacing);
		virtual void UpdateChildSizes() = 0;
		void AddChild(UIElement* child);

		void Render() override;

		void SetAlignment(AlignItems xAlign, AlignItems yAlign );

		inline int GetSpacing() const { return spacing; }
		std::vector<UIElement*> children;

	protected:
		int spacing;
		AlignItems xAlign, yAlign;
	};

}
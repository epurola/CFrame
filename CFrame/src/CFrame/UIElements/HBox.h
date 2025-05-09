#pragma once
#pragma once

#include "Container.h"
#include "../CFrameEvent/CFrameEvent.h"
#include "../Renderer/Renderer1.h"

namespace CFrame
{
	class CFRAME_API HBox : public Container
	{
	public:
		HBox(int x, int y, int w, int h, UIElement* parent = nullptr);

		explicit HBox()
			: HBox(0, 0, -1, -1, nullptr) {}

		explicit HBox(int w, int h)
			: HBox(0, 0, w, h, nullptr) {}

		~HBox();

		void UpdateChildSizes() override;

		ElementType GetElementType() const override { return ElementType::CONTAINER; };

	private:
		int fixedWidth     = 0;
		int flexWidth      = 0;
		int flexibleCount  = 0;
		int maxChildHeight = 0;
		int totalMargins   = 0;
		int totalSpacing   = 0;
		int availableSpace = 0;

	private:
		void UpdateAlignment(int& xpos, int& ypos);
		void ResetLayoutMetrics();
		void PrecalculateLayoutMetrics();
		void HandleAbsolutePosition(UIElement& child);

	};
}
#pragma once

#include "Container.h"
#include "../CFrameEvent/CFrameEvent.h"

namespace CFrame
{
	class CFRAME_API VBox : public Container
	{
	public:
		VBox(int x, int y, int w, int h, UIElement* parent = nullptr);

		explicit VBox()
			: VBox(0, 0, -1, -1, nullptr) {}

		explicit VBox(int w, int h)
			: VBox(0, 0, w, h, nullptr) {}

		~VBox();

		void UpdateChildSizes() override;

		inline ElementType GetElementType() const override { return ElementType::CONTAINER; };

	private:
		int fixedHeight = 0;
		int flexibleCount = 0;
		int maxChildWidth = 0;
		int flexibleHeight = 0;
		int totalMargins = 0;
		int totalSpacing = 0;
		int availableSpace = 0;

	private:
		void UpdateAlignment(int& xpos, int& ypos);
		void ResetLayoutMetrics();
		void PrecalculateLayoutMetrics();
		void HandleAbsolutePosition(UIElement& child);

	};
}
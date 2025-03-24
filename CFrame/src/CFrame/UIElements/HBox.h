#pragma once
#pragma once

#include "Container.h"
#include "../Core.h"
#include "../Renderer/Renderer.h"
#include "../CFrameEvent/CFrameEvent.h"

namespace CFrame
{
	class CFRAME_API HBox : public Container
	{
	public:
		HBox(int x, int y, int w, int h, UIElement* parent = nullptr);

		explicit HBox()
			: HBox(0, 0, -1, -1, nullptr) {
		}

		explicit HBox(int w, int h)
			: HBox(0, 0, w, h, nullptr) {
		}

		~HBox();

		void Render(Renderer& renderer) override;
		void UpdateChildSizes() override;

		void OnEvent(CFrameEvent& event) override;
		inline ElementType GetElementType() const override { return ElementType::CONTAINER; };

	private:

	};
}
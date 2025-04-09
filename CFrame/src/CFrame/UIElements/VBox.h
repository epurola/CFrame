#pragma once

#include "Container.h"
#include "../Core.h"
#include "../Renderer/Renderer.h"
#include "../CFrameEvent/CFrameEvent.h"

namespace CFrame 
{
	class CFRAME_API VBox : public Container
	{
	public:
		VBox(int x, int y, int w, int h, UIElement* parent = nullptr);

		explicit VBox()
			: VBox(0, 0, -1, -1, nullptr) {
		}

		explicit VBox(int w, int h)
			: VBox(0, 0, w, h, nullptr) {
		}

		~VBox();

		void Render(Renderer& renderer) override; //ToDo: Move to container
		void UpdateChildSizes() override;

		
		inline ElementType GetElementType() const override { return ElementType::CONTAINER; };

	private:

	};
}
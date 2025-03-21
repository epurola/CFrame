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
		VBox(int w, int h);
		~VBox();

		void Render(Renderer& renderer) override;
		void UpdateChildSizes() override;

		void OnEvent(CFrameEvent& event) override;
		

	private:

	};



}
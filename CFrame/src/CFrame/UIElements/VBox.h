#pragma once

#include "Container.h"
#include "../Core.h"

namespace CFrame 
{
	class CFRAME_API VBox : public Container
	{
	public:
		VBox(int w, int h);
		~VBox();

		void UpdateChildSizes() override;

	private:

	};



}
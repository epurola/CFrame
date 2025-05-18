#include "Scale.h"

namespace CFrame 
{
	void Scale::Update(float timestep, UIElement& element) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float scale = startScale + t * (endScale - startScale);
		element.SetScale(scale, scale);

		if (t >= 1.0f) 
		{
			animating = false;
			element.StopAnimation();
		}
	}
}
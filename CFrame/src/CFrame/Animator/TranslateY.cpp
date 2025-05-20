#include "TranslateY.h"

namespace CFrame
{
	void TranslateY::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float newY = startPos + t * (endPos - startPos);
		element.SetY(newY);

		if (t >= 1.0f)
		{
			animating = false;
			element.StopAnimation();
		}
	}
}

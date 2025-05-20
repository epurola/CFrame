#include "TranslateX.h"

namespace CFrame
{
	void TranslateX::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float newX = startPos + t * (endPos - startPos);
		element.SetX(newX);

		if (t >= 1.0f)
		{
			animating = false;
			element.StopAnimation();
		}
	}
}
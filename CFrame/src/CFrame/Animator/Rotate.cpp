#include "Rotate.h"

namespace CFrame 
{
	void Rotate::Update(float timestep)
	{
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float angle = startAngle + t * (endAngle - startAngle);
		element.SetAngle(angle);

		if (t >= 1.0f)
		{
			animating = false;
			element.StopAnimation();
		}
	}
}


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

			if (AnimationEndBehavior::Reset == ending) {
				element.SetAngle(startAngle);
			}
			if (AnimationEndBehavior::Reverse == ending) {
				elapsed = 0.0f;

				element.StartAnimation<Rotate>(
					endAngle,
					startAngle,
					duration,
					AnimationEndBehavior::None
				);
			}
		}
	}
}


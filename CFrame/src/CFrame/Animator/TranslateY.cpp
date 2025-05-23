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
			if (AnimationEndBehavior::Reset == ending) {
				element.SetY(startPos);
			}
			if (AnimationEndBehavior::Reverse == ending) {
				elapsed = 0.0f;

				element.StartAnimation<TranslateY>(
					-(endPos - startPos),
					duration,
					AnimationEndBehavior::None
				);
				return;
			}

			if (onEnd)
			{
				onEnd();
			}
		}
	}
}

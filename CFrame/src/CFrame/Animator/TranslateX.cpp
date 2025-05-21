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
			if (AnimationEndBehavior::Reset == ending) {
				element.SetX(startPos);
			}
			if (AnimationEndBehavior::Reverse == ending) {
				elapsed = 0.0f;

				element.StartAnimation<TranslateX>(
					-(endPos - startPos),
					duration,
					AnimationEndBehavior::None
				);
			}
		}
	}
}
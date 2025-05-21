#include "ScaleY.h"

namespace CFrame
{
	void ScaleY::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float scale = startScale + t * (endScale - startScale);
		element.SetScaleY(scale);

		if (t >= 1.0f)
		{
			animating = false;
			if (AnimationEndBehavior::Reset == end) {
				element.SetScaleY(originalScale);
			}
			if (AnimationEndBehavior::Reverse == end) {
				elapsed = 0.0f;

				element.StartAnimation<ScaleY>(
					endScale,
					startScale,
					duration,
					AnimationEndBehavior::None
				);
			}
		}
	}
}

#include "ScaleX.h"

namespace CFrame
{
	void ScaleX::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float scale = startScale + t * (endScale - startScale);
		element.SetScaleX(scale);

		if (t >= 1.0f)
		{
			animating = false;
			if (AnimationEndBehavior::Reset == end) {
				element.SetScaleX(originalScale);
			}
			if (AnimationEndBehavior::Reverse == end) 
			{
				elapsed = 0.0f;

				element.StartAnimation<ScaleX>(
					endScale,
					startScale,
					duration,
					AnimationEndBehavior::None
				);
				return;
			}

			if (onEnd != nullptr)
			{
				onEnd();
			}
		}
	}
}
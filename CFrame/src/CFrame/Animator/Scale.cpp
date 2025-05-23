#include "Scale.h"

namespace CFrame 
{
	void Scale::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float scale = startScale + t * (endScale - startScale);
		element.SetScale(scale, scale);

		if (t >= 1.0f) 
		{
			animating = false;
			if (AnimationEndBehavior::Reset == end) {
				element.SetScale(originalScale, startScale);
			}
			if (AnimationEndBehavior::Reverse == end) {
				elapsed = 0.0f;
				Scale* anim = new Scale(endScale, startScale, duration, AnimationEndBehavior::None, element);
				anim->onEnd = onEnd;
				element.StartAnimation(anim);
				return;
			}

			if (onEnd != nullptr) 
			{
				onEnd();
			}

		}
	}

}
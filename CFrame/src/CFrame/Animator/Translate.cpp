#include "Translate.h"

namespace CFrame
{
	void Translate::Update(float timestep) {
		animating = true;
		elapsed += timestep;
		float t = std::min(elapsed / duration, 1.0f);

		float newX = startX + t * (endX - startX);
		float newY = startY + t * (endY - startY);

		element.SetX(newX);
		element.SetY(newY);

		if (t >= 1.0f)
		{
			animating = false;
			if (AnimationEndBehavior::Reset == reset) {
				element.SetX(originalX);
				element.SetY(originalY);
			}
			if (AnimationEndBehavior::Reverse == reset) {
				elapsed = 0.0f;
	
				element.StartAnimation<Translate>(
					-(endX - startX),
					-(endY - startY),
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
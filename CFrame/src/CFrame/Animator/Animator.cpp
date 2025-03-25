#include "Animator.h"

namespace CFrame 
{
	Animator::Animator(UIElement& element)
		: isAnimating(false), element(element)
	{
	
	}

	void Animator::Update(float deltaTime)
	{
		if (!isAnimating) return;

		elapsedTime += deltaTime;

		float t = (animationDuration > 0) ? elapsedTime / animationDuration : 1.0f;
		if (t > 1.0f) t = 1.0f;

		element.SetScale(1.0f + t * (1.5f - 1.0f), 1.0f + t * (2.0f - 1.0f), 1.0f); //startscale + t *(targetScale - startScale)

		if (t >= 1.0f) {
			isAnimating = false;
		}
	}

	void Animator::StartAnimation(float duration)
	{
		isAnimating = true;
		animationDuration = duration;
		elapsedTime = 0;
	}

	void Animator::StopAnimation()
	{
		isAnimating = false;
	}
}


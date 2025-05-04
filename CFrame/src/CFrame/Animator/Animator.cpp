#include "Animator.h"
#include "SDL3/SDL.h"



namespace CFrame 
{
	Animator::Animator(UIElement& element)
		: isAnimating(false), element(element), elapsedTime(0)
	{
	
	}

	void Animator::Update(float deltaTime)
	{
		if (!isAnimating) return;

		elapsedTime += deltaTime;

		float t = (animationDuration > 0) ? (float)elapsedTime / animationDuration : 1.0f;
		if (t > 1.0f) t = 1.0f;

		element.AnimateScale(1.0f + t * (element.GetAnimProperties().animScaleX - 1.0f),
			                1.0f + t * (element.GetAnimProperties().animScaleY - 1.0f)); //startscale + t *(targetScale - startScale) 

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

	float Animator::GetTime()
	{
		return (float)SDL_GetTicks() / 1000.0f;
	}
	
}


#pragma once
#include "../UIElements/UIElement.h"

namespace CFrame 
{
	class Animator 
	{
	public:
		Animator(UIElement& element) ;
		~Animator() {};


		void Update(float deltaTime);
		void StartAnimation(float duration);
		void StopAnimation();
		inline bool IsAnimating() const { return isAnimating; }

	private:
		bool isAnimating;
		float animationDuration = 1.0f;
		float elapsedTime;
		UIElement& element;
	};
}
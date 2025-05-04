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
		float GetTime();
		void SetSpeed(float speed);
		//inline float GetSpeed() const { return speed; }
		inline bool IsAnimating() const { return isAnimating; }

	private:
		bool isAnimating = false;
		float animationDuration = 1.0f;
		float elapsedTime = 0.0;
		UIElement& element;
		
	};
}
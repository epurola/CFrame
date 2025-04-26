#include "AnimationManager.h"

namespace CFrame 
{
	AnimationManager::AnimationManager(Window& window)
		:window(window)
	{
		
	}

	AnimationManager::~AnimationManager()
	{
		
	}
	void AnimationManager::RegisterAnimation(UIElement& animatingElement)
	{
		
		animatingElements.insert(&animatingElement);
		
	}

	void AnimationManager::RemoveAnimator(UIElement& animatingElement)
	{
		animatingElements.erase(&animatingElement);
	}

	void AnimationManager::ActivateTextInput()
	{
		window.StartTextInput();
	}

	void AnimationManager::DeActivatetextInput()
	{
		window.StopTextInput();
	}
}


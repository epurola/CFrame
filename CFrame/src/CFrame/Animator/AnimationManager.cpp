#include "AnimationManager.h"

namespace CFrame 
{
	void AnimationManager::RegisterAnimation(UIElement& animatingElement)
	{
		
		animatingElements.insert(&animatingElement);
		
	}

	void AnimationManager::RemoveAnimator(UIElement& animatingElement)
	{
		
		animatingElements.erase(&animatingElement);
	}
}


#pragma once
#include <unordered_set>

namespace CFrame 
{
	class UIElement;

	class AnimationManager 
	{
	public:

		bool IsAnimating() { return !animatingElements.empty(); }

		void RegisterAnimation(UIElement& animatingElement);
		void RemoveAnimator(UIElement& animatingElement);


	private:
		std::unordered_set<UIElement*> animatingElements;
	};
}

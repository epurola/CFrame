#pragma once
#include <unordered_set>
#include "../Window.h"

namespace CFrame 
{
	class UIElement;

	class AnimationManager 
	{
	public:
		AnimationManager(Window& window);
		~AnimationManager();

		bool IsAnimating() { return !animatingElements.empty(); }

		void RegisterAnimation(UIElement& animatingElement);
		void RemoveAnimator(UIElement& animatingElement);

		void ActivateTextInput();
		void DeActivatetextInput();


	private:
		std::unordered_set<UIElement*> animatingElements;
		Window& window;
	};
}

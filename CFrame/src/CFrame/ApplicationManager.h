#pragma once
#include <unordered_set>
#include "Window.h"
namespace CFrame 
{
	class UIElement;

	class ApplicationManager 
	{
	public:
		ApplicationManager(Window& window);
		~ApplicationManager();

		bool IsAnimating() { return !animatingElements.empty(); }

		void RegisterAnimation(UIElement& animatingElement);
		void RemoveAnimator(UIElement& animatingElement);

		void ActivateTextInput();
		void DeActivatetextInput();

		void SubscribeToEvent(std::function<void(CFrameEvent&)> OnEvent);


	private:
		std::unordered_set<UIElement*> animatingElements;
		Window& window;
		EventDispatcher& eventDispatcher;
	};
}

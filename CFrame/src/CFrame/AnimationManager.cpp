#include "AnimationManager.h"

namespace CFrame 
{
	ApplicationManager::ApplicationManager(Window& window)
		:window(window), eventDispatcher(eventDispatcher)
	{
		
	}

	ApplicationManager::~ApplicationManager()
	{
		
	}
	void ApplicationManager::RegisterAnimation(UIElement& animatingElement)
	{
		
		animatingElements.insert(&animatingElement);
		
	}

	void ApplicationManager::RemoveAnimator(UIElement& animatingElement)
	{
		animatingElements.erase(&animatingElement);
	}

	void ApplicationManager::ActivateTextInput()
	{
		window.StartTextInput();
	}

	void ApplicationManager::DeActivatetextInput()
	{
		window.StopTextInput();
	}

	
}


#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <memory>
#include <vector>
#include "UIElements/UIElement.h"

namespace CFrame
{
class CFRAME_API Application
{
public: 
	Application();
	virtual ~Application();

	void OnEvent(CFrameEvent& e);

	void addElement(UIElement* element);


	void run();

private:
	std::unique_ptr<EventDispatcher> eventDispatcher;
	std::vector<UIElement*> UIElements;

	bool running = true;
	
};

//To be defined in CLIENT
Application* CreateApplication();

} // namespace CFrame


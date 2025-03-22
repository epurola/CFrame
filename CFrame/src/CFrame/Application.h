#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <memory>
#include <vector>
#include "UIElements/UIElement.h"
#include "UIElements/VBox.h"

namespace CFrame
{
class CFRAME_API Application
{
public: 
	Application();
	virtual ~Application();

	void OnEvent(CFrameEvent& e);

	void addElement(UIElement* element);
	void SetWindowSize(int width, int height);


	void run();
	std::unique_ptr<VBox> rootContainer;

private:
	std::unique_ptr<EventDispatcher> eventDispatcher;
	std::vector<UIElement*> UIElements;
	
	std::unique_ptr<Window> window;

	bool running = true;
	int windowWidth = 1280;
	int windowHeight = 720;
	
};

//To be defined in CLIENT
Application* CreateApplication();

} // namespace CFrame


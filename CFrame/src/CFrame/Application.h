#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include "UIElements/UIElement.h"
#include "UIElements/VBox.h"
#include "Renderer/Renderer.h"
#include "Animator/AnimationManager.h"

namespace CFrame
{
class CFRAME_API Application
{
public: 
	Application(int width, int height);
	virtual ~Application();

	void OnEvent(CFrameEvent& e);

	void addElement(UIElement* element);
	void SetWindowSize(int width, int height);


	void run();
	void stop();
	void ToggleFullScreen();
	std::unique_ptr<VBox> rootContainer;

private:
	std::unique_ptr<EventDispatcher> eventDispatcher;
	std::vector<UIElement*> UIElements;
	
	std::unique_ptr<Window> window;
	std::unique_ptr<Renderer> renderer;
	std::shared_ptr<AnimationManager> animationManager;

	bool running = true;
	int windowWidth ;
	int windowHeight;
	
};

//To be defined in CLIENT
Application* CreateApplication();

} // namespace CFrame


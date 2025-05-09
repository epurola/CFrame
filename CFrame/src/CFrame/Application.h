#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include "UIElements/UIElement.h"
#include "UIElements/VBox.h"
#include "UIElements/HBox.h"
#include "UIElements/Label.h"
#include "UIElements/Button.h"
#include "Renderer/Renderer1.h"
#include "Renderer/Scene.h"
#include "ApplicationManager.h"

namespace CFrame
{
class CFRAME_API Application
{
public: 
	Application(int width, int height);
	virtual ~Application();

	void OnEvent(CFrameEvent& e);

	void SetWindowSize(int width, int height);

	void run();
	void stop();
	void ToggleFullScreen();
	void InitTitleBar();

	void AddScene(Scene* scene);

private:
	std::unique_ptr<EventDispatcher> eventDispatcher;
	std::unique_ptr<Window> window;
	std::unique_ptr<Renderer1> renderer;
	std::shared_ptr<ApplicationManager> applicationManager;

	HBox* header;
	Button* close;
	Button* minimize;
	Button* toggleMaximize;
	Label* title;

	std::unique_ptr<VBox> titleBarContainer;
	std::unique_ptr<VBox> sceneContainer;


	bool running = true;
	int windowWidth;
	int windowHeight;
	int headerHeight = 75;
	
};

//To be defined in CLIENT
Application* CreateApplication();

} // namespace CFrame


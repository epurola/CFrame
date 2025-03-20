#include "Application.h"
#include "Log.h"
#include "Window.h"

namespace CFrame
{
	Application::Application() 
	{
		eventDispatcher = std::make_unique<EventDispatcher>();

		eventDispatcher->AddListener(CFrameEventType::WindowClosed,
			[this](CFrameEvent& event) { OnEvent(event); });
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(CFrameEvent& e) 
	{
		CF_CORE_INFO("Closing Window");
		if (CFrameEventType::WindowClosed == e.GetEventType()) 
		{
			running = false;
		}
	}

    void Application::run()
	{
		Window window(*eventDispatcher);
		window.Create(1600, 1200, "CFrame");
		while (running) {
			window.OnUpdate();
		}
	}

}

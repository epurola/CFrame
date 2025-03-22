#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Renderer/Renderer.h"
#include <chrono>

namespace CFrame
{
	Application::Application() 
	{
		eventDispatcher = std::make_unique<EventDispatcher>();
		rootContainer = std::make_unique <VBox>(1600, 1200);
		window = std::make_unique<Window>(*eventDispatcher);

		eventDispatcher->AddListener(CFrameEventType::WindowClosed,
			[this](CFrameEvent& event) { OnEvent(event); });

		eventDispatcher->AddListener(CFrameEventType::WindowResized,
			[this](CFrameEvent& event) { OnEvent(event); });

		eventDispatcher->AddListener(CFrameEventType::MouseButtonDown,
			[this](CFrameEvent& event) { OnEvent(event); });
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(CFrameEvent& e) 
	{
		if (CFrameEventType::WindowClosed == e.GetEventType()) 
		{
			CF_CORE_INFO("Closing Window");
			running = false;
		}
		if (CFrameEventType::WindowResized == e.GetEventType())
		{
			CF_CORE_INFO("Resized window {0}, {1}", 
				         dynamic_cast<WindowResizedEvent&>(e).GetWidth(), 
				         dynamic_cast<WindowResizedEvent&>(e).GetHeight());

			//The main pane should be updated
			
			rootContainer->UpdateChildSizes();//Elements must be added to root container
		}

		for (auto& element : UIElements) {
			element->OnEvent(e);
		}
	}

	void Application::addElement(UIElement* element)
	{
		UIElements.push_back(element);
	}

    void Application::run()
	{
		window->Create(1600, 1200, "CFrame");
		Renderer renderer(*window);
		while (running) {
			window->GL_ClearColorBuffer();
			for (auto& element : UIElements) {
				element->Render(renderer); //Here loop thru rootcontainer instead
			}
			window->OnUpdate(); // Add SwapBuffers and HadleInput to Window so input can be doen before draw
		}
	}
}

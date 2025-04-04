#include "Application.h"  
#include "Log.h"  
#include "Window.h"  
#include "Renderer/Renderer.h"  
#include <chrono>  

namespace CFrame  
{  
Application::Application(int width, int height)  
	: windowWidth(width), windowHeight(height)  
{  
	eventDispatcher = std::make_unique<EventDispatcher>();  
	window = std::make_unique<Window>(*eventDispatcher);  
	
	window->SetHeight(windowHeight);  
	window->SetWidth(windowWidth);  
	
	rootContainer = std::make_unique <VBox>(windowWidth, windowHeight);  
	rootContainer->SetAlignment(AlignItems::Start, AlignItems::Start);  
	UIElements.push_back(rootContainer.get());  
	
	eventDispatcher->AddListener(CFrameEventType::WindowClosed,  
		[this](CFrameEvent& event) { OnEvent(event); });  

	eventDispatcher->AddListener(CFrameEventType::WindowResized,  
		[this](CFrameEvent& event) { OnEvent(event); });  

	eventDispatcher->AddListener(CFrameEventType::MouseButtonDown,  
		[this](CFrameEvent& event) { OnEvent(event); });  

	eventDispatcher->AddListener(CFrameEventType::MouseMoved,  
		[this](CFrameEvent& event) { OnEvent(event); });  

	eventDispatcher->AddListener(CFrameEventType::MouseDragged,
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
		e.handled = true;  
	}  
	if (CFrameEventType::WindowResized == e.GetEventType())  
	{  
		CF_CORE_INFO("Resized window {0}, {1}",   
            dynamic_cast<WindowResizedEvent&>(e).GetWidth(),   
            dynamic_cast<WindowResizedEvent&>(e).GetHeight());  

		//The main pane should be updated  
		rootContainer->SetWidth(dynamic_cast<WindowResizedEvent&>(e).GetWidth());  
		rootContainer->SetHeight(dynamic_cast<WindowResizedEvent&>(e).GetHeight());  

		rootContainer->UpdateChildSizes(); 
		
		e.handled = true;  
	}  

	for (auto& element : UIElements) {  
		if (e.handled) { return; }  
		element->OnEvent(e); 
	}  
	if (e.GetEventType() == CFrameEventType::MouseDragged) {
		rootContainer->UpdateChildSizes();
	 }
}  

void Application::addElement(UIElement* element)  
{  
	UIElements.push_back(element);  
}  

void Application::SetWindowSize(int width, int height)  
{  
	windowHeight = height;  
	windowWidth = width;  
}  

   void Application::run()  
{  
	constexpr double target_fps = 60.0;  
	constexpr std::chrono::milliseconds frame_duration(static_cast<int>(1000.0 / target_fps));  

	window->Create(windowWidth, windowHeight, "CFrame");  
	/*Needs to be created after window->Create since there is no 
	valid GL context before that*/
	renderer = std::make_unique<Renderer>(*window);
	

	while (running) {  
		auto start_time = std::chrono::steady_clock::now();  
		window->GL_ClearColorBuffer(); 

		for (auto& element : UIElements) {  
			element->Render(*renderer);   
		}  

		window->OnUpdate(); // Add SwapBuffers and HadleInput to Window so input can be doen before draw  

		auto end_time = std::chrono::steady_clock::now();  
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  

		if (elapsed_time < frame_duration) {  
			std::this_thread::sleep_for(frame_duration - elapsed_time);  
		}  
	}  
}  
}

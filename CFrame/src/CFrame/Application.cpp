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
	window->Create(windowWidth, windowHeight, "CFrame");
	
	window->SetHeight(windowHeight);  
	window->SetWidth(windowWidth);  
	
	applicationManager = std::make_shared<ApplicationManager>(*window);
	
	rootContainer = std::make_unique <VBox>(windowWidth, windowHeight);  
	rootContainer->SetAlignment(AlignItems::Start, AlignItems::Start);  
	InitTitleBar();
	rootContainer->AddChild(header);
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

	eventDispatcher->AddListener(CFrameEventType::MouseScroll,
		[this](CFrameEvent& event) { OnEvent(event); });

	eventDispatcher->AddListener(CFrameEventType::KeyPressed,
		[this](CFrameEvent& event) { OnEvent(event); });

	eventDispatcher->AddListener(CFrameEventType::WindowFullScreen,
		[this](CFrameEvent& event) { OnEvent(event); });

	eventDispatcher->AddListener(CFrameEventType::MouseLeaveWindow,
		[this](CFrameEvent& event) { OnEvent(event); });

	eventDispatcher->AddListener(CFrameEventType::TextInput,
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
		stop();
		e.handled = true;  
	}  

	if (CFrameEventType::WindowResized == e.GetEventType())  
	{  
		//The main pane should be updated  
		int width  = dynamic_cast<WindowResizedEvent&>(e).GetWidth();
		int height = dynamic_cast<WindowResizedEvent&>(e).GetHeight();
		rootContainer->SetWidth(width);  
		rootContainer->SetHeight(height);  
		window->SetWidth(width);
		window->SetHeight(height);

		rootContainer->UpdateChildSizes(); 
		
		e.handled = true;  
	}  

	for (auto& element : UIElements) {  
		if (e.handled) { return; }  
		element->OnEvent(e); 
	}  
	if (e.GetEventType() == CFrameEventType::MouseDragged ) {
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

//TODO: Poll events at a higher frequency
void Application::run()  
{  
	constexpr double target_fps = 100.0;  
	constexpr std::chrono::milliseconds frame_duration(static_cast<int>(1000.0 / target_fps));    
	/*Needs to be created after window->Create since there is no 
	valid GL context before that*/
	renderer = std::make_unique<Renderer>(*window);
	//Inject the manager into each UI element so they can send signals
	for (auto& element : UIElements) {
		element->RegisterAnimator(applicationManager);
	}

	//Currently stops animation if mouse does not move
	while (running ) {  
		 
		bool render = window->OnUpdate(); // Handles even polling return true if there is an event
		auto start_time = std::chrono::steady_clock::now();
		if (render || applicationManager->IsAnimating()) {
			window->GL_ClearColorBuffer();
			for (auto& element : UIElements) {
				element->Render(*renderer);  
				
			}
			window->GL_SwapWindow();
		}

		auto end_time = std::chrono::steady_clock::now();  
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  

		if (elapsed_time < frame_duration) {  
			std::this_thread::sleep_for(frame_duration - elapsed_time);  
		}  
	}  
}
   void Application::stop()
   {
	   running = false;
   }

   void Application::ToggleFullScreen()
   {
	   window->SetFullScreen();
   }

   void Application::InitTitleBar()
   {
	   header = new HBox(-1, 75);
	   minimize = new Button(75, 75);
	   minimize->SetIcon(0xE738);
	   minimize->SetFontSize(24);
	   minimize->SetTextColor(Color::White);
	   minimize->SetRadius(0);
	   minimize->SetColor(Color::DarkGray);

	   minimize->SetOnLeave([&]() { minimize->SetColor(Color::DarkGray); });
	   minimize->SetOnClick([&, this]() { window->MinimizeWindow();});
	   minimize->SetOnHover([&]() {minimize->SetColor(Color::Gray);});

	   toggleMaximize = new Button(75, 75);
	   toggleMaximize->SetIcon(0xE71A);
	   toggleMaximize->SetFontSize(24);
	   toggleMaximize->SetRadius(0);
	   toggleMaximize->SetTextColor(Color::White);
	   toggleMaximize->SetColor(Color::DarkGray);
	   toggleMaximize->SetFont(CFrame::Font::SegoeMDL2Assets);

	   toggleMaximize->SetOnLeave([&]() { toggleMaximize->SetColor(Color::DarkGray);});
	   toggleMaximize->SetOnHover([&]() {toggleMaximize->SetColor(Color::Gray);});
	   toggleMaximize->SetOnClick([&, this]() { ToggleFullScreen();});

	   close = new Button(75, 75);
	   close->SetIcon(0xE711);
	   close->SetFontSize(24);
	   close->SetRadius(0);
	   close->SetTextColor(Color::White);
	   close->SetColor(Color::DarkGray);

	   close->SetOnLeave([&]() { close->SetColor(Color::DarkGray);});
	   close->SetOnHover([&]() {close->SetColor(Color::Red);});
	   close->SetOnClick([&, this]() {stop();});

	   header->AddChild(minimize);
	   header->AddChild(toggleMaximize);
	   header->AddChild(close);
	   header->SetColor(Color::DarkGray);
	   header->SetAlignment(CFrame::AlignItems::End, CFrame::AlignItems::Center);
   }
}

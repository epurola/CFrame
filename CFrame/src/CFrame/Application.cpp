#include "Application.h"  
#include "Log.h"  
#include "Window.h"  
#include <chrono>  
#include "RenderAPI/Renderer2D.h"

namespace CFrame  
{  
Application::Application(int width, int height)  
	: windowWidth(width), windowHeight(height)  
{  
	eventDispatcher = std::make_unique<EventDispatcher>(); 

	window = std::make_unique<Window>(*eventDispatcher); 
	window->Create(windowWidth, windowHeight + headerHeight, "CFrame");
	float scale = window->GetScale();
	windowWidth = window->GetWidth() * scale;
	windowHeight = window->GetHeight() * scale;
	headerHeight *= scale;
	
	window->ResizeWindow(windowWidth , windowHeight );
	window->SetHeight(windowHeight);  
	window->SetWidth(windowWidth);
	camera = std::make_unique<Camera2D>(window->GetWidth(), window->GetHeight());
	Renderer2D::Init(*camera);

	
	applicationManager = std::make_shared<ApplicationManager>(*window);
	titleBarContainer = std::make_unique <VBox>(0,0, windowWidth, headerHeight);  
	titleBarContainer->SetAlignment(AlignItems::Start, AlignItems::Start);  
	InitTitleBar();

	titleBarContainer->AddChild(header);
	//Place at y = 40 since original header height is that and it will be later updated in run method
	//to be the correct pos. Maybe refactor the scaling later...
	sceneContainer = std::make_unique<VBox>(0, 40, windowWidth, windowHeight - headerHeight);
	
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

	eventDispatcher->AddListener(CFrameEventType::MouseButtonReleased,
		[this](CFrameEvent& event) { OnEvent(event); });
}  

Application::~Application()   
{  

}  

void Application::OnEvent(CFrameEvent& e)   
{  
	sceneContainer->OnEvent(e);
	if (e.handled) return;

	titleBarContainer->OnEvent(e);
	if (e.handled) return;

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
		//renderer->Resize(width, height);
		sceneContainer->SetWidth(width);  
		sceneContainer->SetHeight(height - headerHeight); 
		sceneContainer->UpdateChildSizes();
		titleBarContainer->SetWidth(width);
		window->SetWidth(width);
		window->SetHeight(height);
		camera->SetSize(width, height);

		titleBarContainer->UpdateChildSizes();
		
		e.handled = true; 
	}  
	

}  

void Application::run()  
{  
	constexpr double target_fps = 60.0;  
	constexpr std::chrono::milliseconds frame_duration(static_cast<int>(1000.0 / target_fps));    
	/*Needs to be created after window->Create since there is no 
	valid GL context before that*/
	//renderer = std::make_unique<Renderer1>(*window);
	//Inject the manager into each UI element so they can send signals

	titleBarContainer->RegisterAnimator(applicationManager);
	sceneContainer->RegisterAnimator(applicationManager);

	titleBarContainer->UpdateChildSizes();
	sceneContainer->UpdateChildSizes();

	float scale = window->GetScale();

	titleBarContainer->SetScaleFactor(scale);
	sceneContainer->SetScaleFactor(scale);
	
	while (running ) {  
		auto start_time = std::chrono::steady_clock::now();

		bool render = window->OnUpdate(); // Handles even polling return true if there is an event
		
		if (render || applicationManager->IsAnimating()) 
		{
			Renderer2D::Begin();

			//  Render containers 
			titleBarContainer->Render();  
			sceneContainer->Render();

			// End rendering frame
			Renderer2D::End();
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

   void Application::SetWindowSize(int width, int height)
   {
	   windowHeight = height;
	   windowWidth = width;
   }

   void Application::AddScene(Scene* scene)
   {
	   if (!sceneContainer->children.empty()) {
		   sceneContainer->children.clear();
	   }

	   sceneContainer->AddChild(scene->GetRoot());
   }

   void Application::InitTitleBar()
   {
	   header = new HBox(-1, 40);

	   minimize = new Button(40 , 40);
	   minimize->SetIcon(0xE738);
	   minimize->SetFontSize(20 );
	   minimize->SetTextColor(Color::White);
	   minimize->SetRadius(0);
	   minimize->SetColor(Color::DarkGray);

	   title = new Label(-1, 40 );
	   title->SetText("CFrame");

	   minimize->SetOnLeave([&]() { minimize->SetColor(Color::DarkGray); });
	   minimize->SetOnClick([&, this]() { window->MinimizeWindow();});
	   minimize->SetOnHover([&]() {minimize->SetColor(Color::Gray);});

	   toggleMaximize = new Button(40 , 40 );
	   toggleMaximize->SetIcon(0xE71A);
	   toggleMaximize->SetFontSize(20 );
	   toggleMaximize->SetRadius(0);
	   toggleMaximize->SetTextColor(Color::White);
	   toggleMaximize->SetColor(Color::DarkGray);
	   toggleMaximize->SetFont(CFrame::Font::SegoeMDL2Assets);

	   toggleMaximize->SetOnLeave([&]() { toggleMaximize->SetColor(Color::DarkGray);});
	   toggleMaximize->SetOnHover([&]() {toggleMaximize->SetColor(Color::Gray);});
	   toggleMaximize->SetOnClick([&, this]() { ToggleFullScreen();});

	   close = new Button(40 , 40);
	   close->SetIcon(0xE711);
	   close->SetFontSize(20);
	   close->SetRadius(0);
	   close->SetTextColor(Color::White);
	   close->SetColor(Color::DarkGray);

	   close->SetOnLeave([&]() { close->SetColor(Color::DarkGray);});
	   close->SetOnHover([&]() {close->SetColor(Color::Red);});
	   close->SetOnClick([&, this]() {stop();});

	   header->AddChild(title);
	   header->AddChild(minimize);
	   header->AddChild(toggleMaximize);
	   header->AddChild(close);
	   header->SetColor(Color::DarkGray);
	   header->SetAlignment(CFrame::AlignItems::End, CFrame::AlignItems::Center);
   }
}

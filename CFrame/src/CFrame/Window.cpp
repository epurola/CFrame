#include "Window.h"

namespace CFrame 
{

Window::Window(EventDispatcher& dispather)
		: dispatcher(dispather) { }

Window::~Window()
{
	if (context) {
		SDL_GL_DestroyContext(context);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void Window::OnUpdate()  
{  
   SDL_Event event;  
   while (SDL_PollEvent(&event)) {  
       switch (event.type) {  
       case SDL_EVENT_MOUSE_BUTTON_DOWN: 
	   {
		   MouseButtonDownEvent mouseButtonDownEvent(event.button.x, event.button.y);
		   dispatcher.Dispatch(mouseButtonDownEvent);
           break;  
	   }   
       case SDL_EVENT_KEY_DOWN:  
       {  
           KeyPressedEvent keyEvent(event.key.key, event.key.repeat); 
		   dispatcher.Dispatch(keyEvent);  
           break;  
       } 
	   case SDL_EVENT_MOUSE_MOTION:
	   {
		   MouseMovedEvent mouseMovedEvent(event.motion.x, event.motion.y);
		   dispatcher.Dispatch(mouseMovedEvent);
		   break;
	   }
	   case SDL_EVENT_WINDOW_RESIZED:
	   {
		   SDL_SetWindowSize(window, event.window.data1, event.window.data2);
		   break;
	   }
	   case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
	   {
		   WindowClosedEvent closed;
		   dispatcher.Dispatch(closed);
		   break;
	   }
       default:  
           break;  
       }  
   }  
   SDL_GL_SwapWindow(window);
}


Window& Window::Create(unsigned int width, unsigned int height, const std::string& title)
{
	this->width = width;
	this->height = height;
	this->title = title;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		CF_CORE_ERROR("SDL_Init Error: {} ", SDL_GetError());
    }

	window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		CF_CORE_ERROR("SDL_CreateWindow Error: {0}");
	}

	context = SDL_GL_CreateContext(window);
	if (context = nullptr) {
		CF_CORE_ERROR("SDL_CreateContext Error: {0}");
	}
	
	return *this;
}

} // namespace CFrame
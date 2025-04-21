#include "Window.h"
#include "glad/glad.h"
#include "SDL3/SDL.h"

namespace CFrame 
{

Window::Window(EventDispatcher& dispather)
		: dispatcher(dispather) { }

Window::~Window()
{
	if (context) {
		SDL_GL_DestroyContext(static_cast<SDL_GLContext>(context));
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void Window::OnUpdate()  
{  
   SDL_Event event;
   bool isDragging;
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
			   if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
				   isDragging = true;
				   MouseDraggedEvent dragEvent(event.motion.x - event.motion.xrel, event.motion.y - event.motion.yrel, event.motion.x, event.motion.y);
				   dispatcher.Dispatch(dragEvent);
			   }
		   break;
	   }
	   case SDL_EVENT_WINDOW_RESIZED:
	   {
		   WindowResizedEvent resizedEvent(event.window.data1, event.window.data2);
		   glViewport(0, 0, event.window.data1, event.window.data2);
		   dispatcher.Dispatch(resizedEvent);
		
		   break;
	   }
	   case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
	   {
		   WindowClosedEvent closed;
		   dispatcher.Dispatch(closed);
		   break;
	   }
	   case SDL_EVENT_MOUSE_WHEEL:
	   {
		   MouseScrolledEvent scroll(event.wheel.x, event.wheel.y, event.wheel.mouse_x, event.wheel.mouse_y);
		   dispatcher.Dispatch(scroll);
		   break;
	   }
       default:  
           break;  
       }  
   }  
   SDL_GL_SwapWindow(window);
  
}


void Window::GL_UpdateviewPort(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);

}

void Window::GL_ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SetWidth(int windowWidth)
{
	width = windowWidth;
}

void Window::SetHeight(int windowHeight)
{
	height = windowHeight;
}

Window& Window::Create(unsigned int width, unsigned int height, const std::string& title)
{
	this->width = width;
	this->height = height;
	this->title = title;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		CF_CORE_ERROR("SDL_Init Error: {} ", SDL_GetError());
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		CF_CORE_ERROR("SDL_CreateWindow Error: {0}");
	}


	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		CF_CORE_ERROR("SDL_CreateContext Error: {0}");
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("Failed to initialize GLAD");
		
	}
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	


	return *this;
}

} // namespace CFrame
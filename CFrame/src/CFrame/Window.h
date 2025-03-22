#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <string>
#include "SDL3/SDL.h"
#include "Log.h"


namespace CFrame
{
	class CFRAME_API Window 
	{
	public:
		Window(EventDispatcher& Dispather ) ;
		~Window() ;
		//Called once per frame
		void OnUpdate();

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }
	    SDL_Window* GetWindow() { return window; }
		void GL_UpdateviewPort(int x, int y, int w, int h);
		void GL_ClearColorBuffer();


		 Window& Create(unsigned int width = 1280, 
			unsigned int height = 720, 
			const std::string& title = "CFrame Window");
	private:
		unsigned int width = 1280;
		unsigned int height = 720;
		std::string title;
		SDL_Window* window;
		SDL_GLContext context;
		EventDispatcher& dispatcher;
	};
}

#pragma once
#include "Core.h"
#include "CFrameEvent/CFrameEvent.h"
#include <string>
#include "Log.h"
#include <windows.h>
#include <algorithm>
struct SDL_Window;



namespace CFrame
{
	class CFRAME_API Window 
	{
	public:
		Window(EventDispatcher& Dispather ) ;
		~Window() ;
		//Called once per frame
		bool OnUpdate();

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }
	    SDL_Window* GetWindow() { return window; }
		void GL_UpdateviewPort(int x, int y, int w, int h);
		void GL_ClearColorBuffer();
		void GL_SwapWindow();
		void SetWidth(int w);
		void SetHeight(int h);
		void SetFullScreen();
		void MinimizeWindow();
		void StartTextInput();
		void StopTextInput();
		void ResizeWindow(int width, int height);

		void SetBorderColor(HWND hwnd, COLORREF borderColor);

		float GetScaleFactorForWindow(HWND hwnd);

		float GetScale() const { return scaleFactor; }
		
		 Window& Create(unsigned int width = 1280, 
			unsigned int height = 720, 
			const std::string& title = "CFrame Window");
	private:
		unsigned int width = 1280;
		unsigned int height = 720;
		std::string title = "CFrame";
		SDL_Window* window;
		void* context; // holds SDL_GLContext
		EventDispatcher& dispatcher;
		float scaleFactor;
	};
}

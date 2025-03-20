#pragma once
#include "../Window.h"
#include "Glad/Glad.h"

namespace CFrame {

	class Renderer
	{
	public:
		Renderer(Window& window);

		~Renderer();

		void DrawRectangle(float x, float y, float w, float h, SDL_Color color, float angle, int radius);

	private:
		Window* window;
		SDL_FRect rect;
		SDL_Texture* texture = NULL;
		SDL_FColor fcolor;


	};
}

#pragma once
#include <stdint.h>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <memory>
#include "../Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferr.h"
#include "Shader.h"
#include "Texture.h"
#include "SDL3/SDL.h"

namespace CFrame {

	class Renderer
	{
	public:
		Renderer(Window& window);

		~Renderer();

		void DrawRectangle(float x, float y, float w, float h, 
			SDL_Color color, SDL_Color gradient, float angle, int radius, float time, float speed);

	private:
		Window& window;
		SDL_Texture* texture = NULL;
		std::unique_ptr<Shader> shader;
	};
}

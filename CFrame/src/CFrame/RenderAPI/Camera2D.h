#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace CFrame 
{
	class Camera2D 
	{
	public:
		Camera2D(float width, float height)
			:width(width), height(height)
		{
			viewProjection = glm::ortho( 0.0f, width, height, 0.0f, -1.0f ,1.0f );
		}

		const glm::mat4& GetViewProjection() const { return viewProjection; }

		void UpdateProjection() {
			viewProjection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
		}

		void SetSize(float width, float height) {
			this->width = width;
			this->height = height;
			UpdateProjection(); 
		}

		void SetPosition(const glm::vec2& position) {
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
			viewProjection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f) * view;
		}

		float GetWidth()  const { return width; }
		float GetHeight()  const { return height; }

	private:
		glm::mat4 viewProjection;
		float width = 0;
		float height = 0;
	};
}
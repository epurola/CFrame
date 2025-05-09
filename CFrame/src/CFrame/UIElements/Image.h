#pragma once

#include "UIElement.h"
#include "../Renderer/texture.h"
#include "../Renderer/Renderer1.h"

namespace CFrame 
{
	class Image : public UIElement 
	{
	public:
		Image(int x, int y, int w, int h, std::string path, UIElement* parent);
		~Image();

		explicit Image(std::string path)
			: Image(0, 0, -1, -1, path, nullptr) {
		}

		explicit Image(int w, int h , std::string path)
			: Image(0, 0, w, h, path, nullptr) {
		}

		void Render(Renderer1& renderer) override;
		void OnEvent(CFrameEvent& event) override;
		void SetOnEvent(std::function<void()> onEvent);

		ElementType GetElementType() const override { return ElementType::IMAGE; };

	private:
		std::unique_ptr<Texture> imageTexture;
		std::function<void()> onEvent;
	};
}
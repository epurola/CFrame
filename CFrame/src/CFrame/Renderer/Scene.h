#pragma once
#include <vector>
#include <memory>
#include "../UIElements/UIElement.h"
#include "../UIElements/VBox.h"

namespace CFrame {
	
	class Scene {
	public:
		Scene() ;
		Scene(int width, int height);
		virtual ~Scene() = default;

		virtual void OnCreate(int width, int height);
		virtual void OnDestroy();
		virtual void OnEvent(CFrameEvent& e, float deltaTime);
		virtual void OnRender(Renderer& renderer, float time);

		UIElement* GetRoot();

		void AddElement(UIElement* element);
		const std::vector<UIElement*>& GetElements() const;

	protected:
		std::vector<UIElement*> elements;
		std::unique_ptr<VBox> sceneContainer;


	};
	
}
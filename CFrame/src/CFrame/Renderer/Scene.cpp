#include "Scene.h"

namespace CFrame 
{
	Scene::Scene() 
	{
		sceneContainer = std::make_unique<VBox>();
	}

	Scene::Scene(int width, int height) 
	{
		sceneContainer = std::make_unique<VBox>(width, height);
	}

	void Scene::OnCreate(int width, int height)
	{
		
	}

	void Scene::OnDestroy()
	{
		elements.clear();
	}

	void Scene::OnEvent(CFrameEvent& e, float deltaTime)
	{
		sceneContainer->OnEvent(e);
	}

	void Scene::OnRender(Renderer1& renderer, float time)
	{
		sceneContainer->Render(renderer);
	}

	UIElement* Scene::GetRoot() 
	{
		return sceneContainer.get();
	}
	
	void Scene::AddElement(UIElement* element) {
		sceneContainer->AddChild(element);
		elements.push_back(element);
	}

	const std::vector<UIElement*>& Scene::GetElements() const
	{
		return elements;
	}

}


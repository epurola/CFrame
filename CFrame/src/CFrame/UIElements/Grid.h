#pragma once
#include "Container.h"


namespace CFrame 
{
	struct Cell 
	{
		UIElement* child = nullptr;
	};

	class Grid : public Container 
	{
	public:
		Grid(int x, int y, int w, int h, UIElement* parent = nullptr);

		explicit Grid()
			: Grid(0, 0, -1, -1, nullptr) {
		}

		explicit Grid(int w, int h)
			: Grid(0, 0, w, h, nullptr) {
		}

		~Grid();

		void UpdateChildSizes() override;
		void AddChild(UIElement* child, int index);

		void SetLayout(int rows, int cols);

		UIElement* GetChild(int index);
		void RemoveChild(int index);
		void InsertChild(UIElement* child, int index);

		ElementType GetElementType() const override { return ElementType::CONTAINER; };
	private:
		int rows = 4;
		int cols = 4;
		float gridWidth = 0;
		float gridHeight = 0;

		std::vector<Cell> cells;
	};
}
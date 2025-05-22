#include "Grid.h"

namespace CFrame 
{
	Grid::Grid(int x, int y, int w, int h, UIElement* parent)
		:Container(x,y,w,h, parent)
	{
		isHeightResizable = (h == -1);
		isWidthResizable = (w == -1);
		SetColor(Color::LightGray2);
		cells.assign(rows * cols, Cell());
	}

	Grid::~Grid()
	{

	}

	//Todo add more spacing options
	void Grid::UpdateChildSizes()
	{
		if (children.empty()) return;

		float gridWidth = 0;
		float gridHeight = 0;

		gridWidth = GetWidth() / cols;
		gridHeight = GetHeight() / rows;

		float xpos = GetX() +(float) properties.padding;
		float ypos = GetY() +(float) properties.padding;

		int col = 0;

		for (auto& cell : cells)
		{
			UIElement* child = cell.child;

			//if (!child->IsVisible()) continue;
			if (child != nullptr) 
			{
				child->SetX(xpos);
				child->SetY(ypos);
				child->SetWidth(gridWidth);
				child->SetHeight(gridHeight);

				child->UpdateVertices();//Update the drawing info of the child
				child->UpdateChildSizes();
			}

			col++;

			if (col >= cols)
			{
				col = 0;
				xpos = GetX() + properties.padding;
				ypos += gridHeight;
			}
			else
			{
				xpos += gridWidth;
			}
		}
	}

	void Grid::AddChild(UIElement* child, int index)
	{
		if (index < 0 || index >= cells.size()) return;
	    //Add the child to the children vector so it gets drawn
		Container::AddChild(child);
		cells[index].child = child;  
	}

	void Grid::SetLayout(int rows, int cols)
	{
		this->rows = rows;
		this->cols = cols;
		cells.assign(rows * cols, Cell());
	}

	UIElement* Grid::GetChild(int index)
	{
		if (index < 0 || index >= static_cast<int>(cells.size())) {
			return nullptr; 
		}

		return cells[index].child;
	}

	void Grid::RemoveChild(int index)
	{
		if (index < 0 || index >= static_cast<int>(cells.size())) {
			return;
		}
		UIElement* target = cells[index].child;
		cells[index].child = nullptr;

		// Remove the target from renderChildren
		auto it = std::remove(renderChildren.begin(), renderChildren.end(), target);
		renderChildren.erase(it, renderChildren.end());
	}

	void Grid::InsertChild(UIElement* child, int index)
	{
		if (index < 0 || index >= static_cast<int>(cells.size())) {
			return;
		}

		if (cells[index].child == nullptr) {
			cells[index].child = child;
			renderChildren.push_back(child); 
		}
	}
}


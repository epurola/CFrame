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

		int xpos = GetX() + properties.padding;
		int ypos = GetY() + properties.padding;

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

}


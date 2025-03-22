#include "UIElement.h"

namespace CFrame {


	UIElement::UIElement(int x, int y, int w, int h, UIElement* parent)
		:x(x), y(y), width(w), height(h), parent(parent)
	{
		if (width == -1 && parent) width = parent->width;
		if (height == -1 && parent) height = parent->height;
	}

	void UIElement::SetMargin(int marginleft, int marginRight, int marginTop, int marginBottom)
	{
		properties.marginBottom = marginBottom;
		properties.marginLeft = marginleft;
		properties.marginTop = marginTop;
		properties.marginRight = marginRight;
	}

	void UIElement::SetPadding(int padding)
	{
		properties.padding = padding;
	}

	void UIElement::SetParent(UIElement* p)
	{
		this->parent = p;
	}

	void UIElement::SetHeight(int h)
	{
		this->height = h;
	}

	void UIElement::SetWidth(int w)
	{
		this->width = w;
	}

	void UIElement::SetX(int x)
	{
		this->x = x;
	}

	void UIElement::SetY(int y)
	{
		this->y = y;
	}

	ElementProperties& UIElement::GetProperties()
	{
		return properties;
	}

}

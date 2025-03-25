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

	void UIElement::SetRadius(int r)
	{
		properties.radius = r;
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

	void UIElement::SetColor(Color color)
	{
		this->color = color;
	}

	void UIElement::SetScale(float scaleX, float scaleY, float duration)
	{
		if (duration > 0.0f) {
			isAnimatedElement = true;
			this->properties.duration = duration;
		}
		this->properties.scaleX = scaleX;
		this->properties.scaleY = scaleY;
	}

	void UIElement::AnimateScale(float scaleX, float scaleY)
	{
		this->properties.animScaleX = scaleX;
		this->properties.animScaleY = scaleY;
	}

	ElementProperties& UIElement::GetProperties()
	{
		return properties;
	}

}

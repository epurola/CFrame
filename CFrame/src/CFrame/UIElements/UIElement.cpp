#include "UIElement.h"

namespace CFrame {


	UIElement::UIElement(int x, int y, int w, int h, UIElement* parent)
		:x(x), y(y), width(w), height(h), parent(parent)
	{
		if (width == -1 && parent) width = parent->width;
		if (height == -1 && parent) height = parent->height;
		isHeightResizable = true;
		isWidthResizable = true;
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

	void UIElement::SetRadius(float topLeft, float topRight, float bottoLeft, float bottomRight)
	{
		
		properties.radius.bottomLeft = bottoLeft;
		properties.radius.bottomRight = bottomRight;
		properties.radius.topLeft = topLeft;
		properties.radius.topRight = topRight;
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

	void UIElement::SetAngle(float angle)
	{
		properties.angle = angle;
	}

	void UIElement::SetBorder(float border)
	{
		this->properties.border = border;
	}

	void UIElement::SetBorderColor(Color color1)
	{
		this->properties.borderColor1 = color1;
		this->properties.borderColor2 = color1;
	}

	void UIElement::SetBorderGradient(Color color1, Color color2)
	{
		this->properties.borderColor1 = color1;
		this->properties.borderColor2 = color2;
	}

	void UIElement::SetOpacity(float opacity)
	{
		properties.opacity = opacity;
	}

	void UIElement::SetColor(Color color)
	{
		this->properties.color1 = color;
		this->properties.color2 = color;
	}
	void UIElement::SetGradient(Color color1, Color color2)
	{
		this->properties.color1 = color1;
		this->properties.color2 = color2;
	}
	void UIElement::SetOnLeave(std::function<void()> onLeave)
	{
		this->onLeave = onLeave;
	}

	void UIElement::SetOnHover(std::function<void()> onHover)
	{
		this->onHover = onHover;
	}

	/*By providing a time to SetScale the scaling becomes animated otherwise it is
	applied to the width and height permanently*/
	void UIElement::SetScale(float scaleX, float scaleY)
	{
		this->properties.scaleX = scaleX;
		this->properties.scaleY = scaleY;
	}

	void UIElement::AnimateScale(float scaleX, float scaleY)
	{
		this->properties.scaleX = scaleX;
		this->properties.scaleY = scaleY;
	}

	void UIElement::AnimateGradient(float speed)
	{
		this->animProperties.speed = speed;
	}


}

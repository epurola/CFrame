#include "UIElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>    
#include <glm/gtc/matrix_transform.hpp>

namespace CFrame {
#define M_PI 3.14159265358979323846


	UIElement::UIElement(int x, int y, int w, int h, UIElement* parent)
		:x(x), y(y), width(w), height(h), parent(parent)
	{
		if (width == -1 && parent) width = parent->width;
		if (height == -1 && parent) height = parent->height;
		
	}

	void UIElement::OnEvent(CFrameEvent& event)
	{
		//Default
	}

	void UIElement::UpdateVertices()
	{
		properties.vertices.bottomLeftX = x;
		properties.vertices.bottomLeftY = y;

		properties.vertices.bottomRightX = x + width;
		properties.vertices.bottomRightY = y;

		properties.vertices.topLeftX = x;
		properties.vertices.topLeftY = y + height;

		properties.vertices.topRightX = x + width;
		properties.vertices.topRightY = y + height;

		if (properties.angle > 0.0f) {
			
			float cX = x + (GetWidth() / 2.0f);
			float cY = y + (GetHeight() / 2.0f);

			float angle = properties.angle * M_PI / 180.0f;
			float cosA = cos(angle);
			float sinA = sin(angle);

	
		   //x' = cos(θ)⋅(x−cx)−sin(θ)⋅(y−cy) + cx
		   //y' = sin(θ)⋅(x−cx)+cos(θ)⋅(y−cy)+cy
		float dx = properties.vertices.bottomLeftX - cX;
        float dy = properties.vertices.bottomLeftY - cY;
        properties.vertices.bottomLeftX = cX + cosA * dx - sinA * dy;
        properties.vertices.bottomLeftY = cY + sinA * dx + cosA * dy;

        // Rotate bottom-right vertex
        dx = properties.vertices.bottomRightX - cX ;
        dy = properties.vertices.bottomRightY - cY ;
        properties.vertices.bottomRightX = cX + cosA * dx - sinA * dy;
        properties.vertices.bottomRightY = cY + sinA * dx + cosA * dy;

        // Rotate top-left vertex
        dx = properties.vertices.topLeftX - cX;
        dy = properties.vertices.topLeftY - cY ;
        properties.vertices.topLeftX = cX + cosA * dx - sinA * dy;
        properties.vertices.topLeftY = cY + sinA * dx + cosA * dy;

        // Rotate top-right vertex
        dx = properties.vertices.topRightX - cX ;
        dy = properties.vertices.topRightY - cY ;
        properties.vertices.topRightX = cX + cosA * dx - sinA * dy;
		properties.vertices.topRightY = cY + sinA * dx + cosA * dy;

		}


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
		if (height < properties.minHeight && properties.minHeight != 0) {
			height = properties.minHeight;
		}
	}

	void UIElement::SetWidth(int w)
	{
		this->width = w;
		if (width > properties.maxWidth && properties.maxWidth != -1) {
			width = properties.maxWidth;
		}
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
		this->properties.borderBottom = border;
		this->properties.borderTop = border;
		this->properties.borderRight = border;
		this->properties.borderLeft = border;
	}

	void UIElement::SetBorder(float t, float b, float r, float l)
	{
		this->properties.borderBottom = b;
		this->properties.borderTop = t;
		this->properties.borderRight = r;
		this->properties.borderLeft = l;
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

	void UIElement::SetMaxWidth(int maxWidth)
	{
		properties.maxWidth = maxWidth;
	}

	void UIElement::SetMinHeight(int minHeight)
	{
		properties.minHeight = minHeight;
		height = minHeight;
	}

	void UIElement::SetZindex(float index)
	{
		properties.zIndex = index;
	}

	void UIElement::SetPositionAbsolute(bool b)
	{
		this->positionAbsolute = b;
		localX = x;
		localY = y;
	}

	void UIElement::SetBackgroundImage(std::string path)
	{
		imageTexture = std::make_unique<Texture>(path);
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

	void UIElement::SetScale(float scaleX, float scaleY)
	{
		this->properties.scaleX = scaleX;
		this->properties.scaleY = scaleY;
	}

	void UIElement::SetVisibility(bool visibility)
	{
		this->isVisible = visibility;
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

	void UIElement::SetDragToResize(bool b)
	{
		dragToResize = b;
	}

	void UIElement::SetAnchorPoint(PositionMode mode)
	{
		pMode = mode;
	}

	void UIElement::SetOverflow(bool allow)
	{
		overflow.overflow = allow;
	} 
	

}

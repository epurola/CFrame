#include "UIElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>    
#include <glm/gtc/matrix_transform.hpp>
#include "Container.h"

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
	//ToDo: Add flags if this needs to recalculate or not
	void UIElement::UpdateVertices()
	{
		float centerX = x + width / 2.0f;
		float centerY = y + height / 2.0f;

		float scaledHalfWidth = (width / 2.0f) * properties.scaleX;
		float scaledHalfHeight = (height / 2.0f) * properties.scaleY;

		properties.vertices.bottomLeft.x = centerX - scaledHalfWidth;
		properties.vertices.bottomLeft.y = centerY - scaledHalfHeight;

		properties.vertices.bottomRight.x = centerX + scaledHalfWidth;
		properties.vertices.bottomRight.y = centerY - scaledHalfHeight;

		properties.vertices.topLeft.x = centerX - scaledHalfWidth;
		properties.vertices.topLeft.y = centerY + scaledHalfHeight;

		properties.vertices.topRight.x = centerX + scaledHalfWidth;
		properties.vertices.topRight.y = centerY + scaledHalfHeight;
		/*
		if (properties.angle > 0.0f) {

			float angleRadians = properties.angle * M_PI / 180.0f;
			float cosA = cos(angleRadians);
			float sinA = sin(angleRadians);
			
		    float cX = x + (GetWidth() / 2.0f);
			float cY = y + (GetHeight() / 2.0f);

	        // Rotate bottom-left vertex
		    RotatePoint(properties.vertices.bottomLeft, properties.angle, cosA, sinA, cX, cY); 

            // Rotate bottom-right vertex
		    RotatePoint(properties.vertices.bottomRight, properties.angle, cosA, sinA, cX, cY);

            // Rotate top-left vertex
		    RotatePoint(properties.vertices.topLeft, properties.angle, cosA, sinA, cX, cY);

            // Rotate top-right vertex
		    RotatePoint(properties.vertices.topRight, properties.angle, cosA, sinA, cX, cY);
		}
		*/
	}
	//Todo: Maybe also take the center in as a point
	void UIElement::RotatePoint(Point& p, float angle, float cosA, float sinA, float cX, float cY)
	{
		float dx = p.x - cX;
		float dy = p.y - cY;
		//x' = cos(θ)⋅(x−cx)−sin(θ)⋅(y−cy) + cx
		//y' = sin(θ)⋅(x−cx)+cos(θ)⋅(y−cy) + cy
		p.x = cX + cosA * dx - sinA * dy;
		p.y = cY + sinA * dx + cosA * dy;
	}

	void UIElement::RegisterAnimator(std::shared_ptr<ApplicationManager> manager)
	{

	}

	void UIElement::SetAnimator(std::unique_ptr<Animator> anim) 
	{
	
		animator = std::move(anim);
		applicationManager->RegisterAnimation(*this);
	}

	void UIElement::StopAnimation()
	{
		applicationManager->RemoveAnimator(*this);
	}


	void UIElement::SetMargin(int left, int right, int top, int bottom)
	{
		properties.margin.left = left;
		properties.margin.right = right;
		properties.margin.top = top;
		properties.margin.bottom = bottom;
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

	void UIElement::SetHeight(float h)
	{
		this->height = h;
		if (height < properties.minHeight && properties.minHeight != 0) {
			height = properties.minHeight;
		}
	}

	void UIElement::SetWidth(float w)
	{
		this->width = w;
		if (width > properties.maxWidth && properties.maxWidth != -1) {
			width = properties.maxWidth;
		}
		if (width < properties.minWidth && properties.minWidth != -1) {
			width = properties.minWidth;
		}
	}

	void UIElement::SetX(float x)
	{
		this->x = x;
	}

	void UIElement::SetY(float y)
	{
		this->y = y;
	}

	void UIElement::SetAngle(float angle)
	{
		properties.angle = angle;
	}

	void UIElement::SetBorder(float border)
	{
		this->properties.border.top = border;
		this->properties.border.bottom = border;
		this->properties.border.right = border;
		this->properties.border.left = border;
	}

	void UIElement::SetBorder(float t, float b, float r, float l)
	{
		this->properties.border.top = t;
		this->properties.border.bottom = b;
		this->properties.border.right = r;
		this->properties.border.left = l;
	}

	void UIElement::SetBorderColor(Color color1, std::optional<Color> color2)
	{
		glm::vec4 c1 = color1.ToVec4();
		glm::vec4 c2 = color2.has_value() ? color2.value().ToVec4() : c1;

		properties.colors.border1 = c1;
		properties.colors.border2 = c2;
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

	void UIElement::SetMinWidth(int minHWidth)
	{
		this->properties.minWidth = minHWidth;
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

	void UIElement::SetColor(Color color, std::optional<Color> color2)
	{
		glm::vec4 c1 = {
		color.r / 255.0f,
		color.g / 255.0f,
		color.b / 255.0f,
		color.a / 255.0f
		};

		glm::vec4 c2 = c1;
		if (color2.has_value()) {
			const Color& col2 = color2.value();
			c2 = {
				col2.r / 255.0f,
				col2.g / 255.0f,
				col2.b / 255.0f,
				col2.a / 255.0f
			};
		}

		properties.colors.background1 = c1;
		properties.colors.background2 = c2;
	}
	
	void UIElement::SetOnLeave(std::function<void()> onLeave)
	{
		this->onLeave = onLeave;
	}

	bool UIElement::MouseDragEvent(MouseDraggedEvent& event)
	{
		//Default implementasion for dragging here...
		return false;
	}

	bool UIElement::MousePressEvent(MouseButtonDownEvent& event)
	{
		return false;
	}

	bool UIElement::MouseReleaseEvent(MouseButtonReleasedEvent& event)
	{
		return false;
	}

	bool UIElement::MouseMoveEvent(MouseMovedEvent& event)
	{
		return false;
	}

	bool UIElement::MouseLeaveEvent()
	{
		return false;
	}

	void UIElement::SetOnHover(std::function<void()> onHover)
	{
		this->onHover = onHover;
	}

	void UIElement::SetScale(float scaleX, float scaleY)
	{
		this->properties.scaleX = scaleX;
		this->properties.scaleY = scaleY;

		UpdateVertices();
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

	void UIElement::SetIsDirty(bool b)
	{
		isDirty = b; // Always mark *this* firs
	
		if (b && parent) {
			parent->isDirty = true; //todo: Call Containers IsDirty that updates children to be dirty
		}
	}

	void UIElement::SetTextColor(Color color1, std::optional<Color> color2)
	{
		if (color2.has_value()) {
			textProps.color1 = color1;
			textProps.color2 = color2.value();
		}
		else {
			textProps.color1 = color1;
			textProps.color2 = color1;
		}
	}

	void UIElement::SetTextAlign(TextAlign alignX)
	{
		textProps.textAlign = alignX;
	}

	void UIElement::SetScaleFactor(float scale)
	{
		scaleFactor = scale;
		// Scale position and size
		x *= scale;
		y *= scale;
		width *= scale;
		height *= scale;

		// Scale text font size properly
		textProps.fontSize = static_cast<int>(textProps.fontSize * scale);

		properties.padding *= scale;
		localX *= scale;
		localY *= scale;
	}


	

}

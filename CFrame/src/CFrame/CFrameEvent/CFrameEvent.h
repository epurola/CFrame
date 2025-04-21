#pragma once

#include "../Core.h"
#include <functional>
#include <unordered_map>
#include <vector>


namespace CFrame
{
	enum class CFrameEventType
	{
		None,
		KeyPressed,
		KeyReleased,
		MouseMoved,
		MouseButtonDown,
		MouseButtonReleased,
		MouseDragged,
		MouseScroll,
		WindowResized,
		WindowClosed
	};

	class CFrameEvent 
	{
	public:
		virtual ~CFrameEvent() = default;
		virtual CFrameEventType GetEventType() const = 0;
		bool handled = false;
	};

	/*Key press event*/
	class CFRAME_API KeyPressedEvent : public CFrameEvent 
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: keyCode(keycode), repeatCount(repeatCount) {}

		inline int GetKeyCode() const { return keyCode; }
		inline int GetRepeatCount() const { return repeatCount; }

		CFrameEventType GetEventType() const override { return CFrameEventType::KeyPressed; }
	private:
		int keyCode;
		int repeatCount;
	};

	/*Key release event*/
	class CFRAME_API KeyReleasedEvent : public CFrameEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: keyCode(keyCode) {}

		inline int GetKeyCode() const { return keyCode; }

		CFrameEventType GetEventType() const override { return CFrameEventType::KeyReleased; }
	private:
		int keyCode;
	};

	/*Window Resized event*/
	class CFRAME_API WindowResizedEvent : public CFrameEvent
	{
	public:
		WindowResizedEvent(int width, int height)
			: width(width), height(height) {
		}

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }

		CFrameEventType GetEventType() const override { return CFrameEventType::WindowResized; }
	private:
		int width;
		int height;
	};

	/*Window Closed event*/
	class CFRAME_API WindowClosedEvent : public CFrameEvent
	{
	public:
		WindowClosedEvent() {} ;

		CFrameEventType GetEventType() const override { return CFrameEventType::WindowClosed; }
	};

	/*Mouse move event*/
	class CFRAME_API MouseMovedEvent : public CFrameEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: mouseX(x), mouseY(y) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		CFrameEventType GetEventType() const override { return CFrameEventType::MouseMoved; }
	private:
		float mouseX, mouseY;
	};

	/*Mouse Button Down event*/
	class CFRAME_API MouseButtonDownEvent : public CFrameEvent
	{
	public:
		MouseButtonDownEvent(float x, float y)
			: mouseX(x), mouseY(y) {
		}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		CFrameEventType GetEventType() const override { return CFrameEventType::MouseButtonDown; }
	private:
		float mouseX, mouseY;
	};

	/*Mouse Dragged event*/
	class CFRAME_API MouseDraggedEvent : public CFrameEvent
	{
	public:
		MouseDraggedEvent(float startX, float startY, float currentX, float currentY)
			: startX(startX), startY(startY), currentX(currentX), currentY(currentY) {
		}

		inline float GetStartX()   const { return startX; }
		inline float GetStartY()   const { return startY; }
		inline float GetCurrentX() const { return currentX; }
		inline float GetCurrentY() const { return currentY; }
		

		CFrameEventType GetEventType() const override { return CFrameEventType::MouseDragged; }
	private:
		float startX, startY;
		float currentX, currentY;
	};

	/*Mouse Scroll event*/
	class CFRAME_API MouseScrolledEvent : public CFrameEvent
	{
	public:
		MouseScrolledEvent(float startX, float startY, float mouseX, float mouseY )
			: distanceX(startX), distanceY(startY), mouseX(mouseX), mouseY(mouseY) {
		}

		inline float GetDistanceX() const { return distanceX; }
		inline float GetDistanceY() const { return distanceY; }
		inline float GetMouseX() const { return mouseX; }
		inline float GetMouseY() const { return mouseY; }



		CFrameEventType GetEventType() const override { return CFrameEventType::MouseScroll; }
	private:
		float distanceX, distanceY;
		float mouseX, mouseY;
	};

	/*Event dispatcher */
	using EventCallBack = std::function<void(CFrameEvent&)>;

	class CFRAME_API EventDispatcher
	{
	public:
		//Register a listener for a spesific type of event
		void AddListener(CFrameEventType type, EventCallBack callback)
		{
			listeners[type].push_back(callback);
		}

		//Dispatch an event to all listeners
		void Dispatch(CFrameEvent& event)
		{
			auto& callbacks = listeners[event.GetEventType()];
			for (auto& callback : callbacks) {
				callback(event);
				if (event.handled) break;
			}
		}
	private:
		std::unordered_map<CFrameEventType, std::vector<EventCallBack>> listeners;

	};
}

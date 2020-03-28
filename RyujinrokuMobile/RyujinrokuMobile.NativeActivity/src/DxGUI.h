#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Task.h"


namespace DxGUI {
	class MouseEvent {
	private:
		int mouseType;
		int mouseX;
		int mouseY;
		int mouseX_prev;
		int mouseY_prev;
		int mouseVectX;
		int mouseVectY;
	public:
		MouseEvent();
		void setMouseType(int mouseType);
		void update();
		bool isPress();
		int getMouseVectX();
		int getMouseVectY();
		int getMousePositionX();
		int getMousePositionY();
	};

	class MouseClickEvent {
	public:
		virtual void onClick(Task* sender) {
		}
		virtual void onRelease(Task* sender) {
		}
	};

	class TextFieldEventHandler {
	public:
		virtual void onTextInputComplete(Task* sender) {

		}
	};

	class MouseCursor : public Task {
	public:
		virtual bool update() override;
		virtual void draw() override;
	};

	class Button : public Task {
	private:
		int instanceId;
		enum STATE {
			BTNID_IDLE,
			BTNID_PRESS,
			BTNID_DISABLE,
		};
		std::string text;
		VECTOR pos;
		VECTOR size;
		unsigned int color;
		unsigned int pressColor;
		STATE state;
		STATE stateNext;
		bool isPress;
		bool isPress_prev;
		bool isPressTrigger;
		bool isHit;
		bool isFirst;
		MouseClickEvent* eventHandler;
	public:
		Button(std::string text, VECTOR pos, VECTOR size, unsigned int color, unsigned int pressColor, MouseClickEvent* eventHandler, int instanceId);
		int getInstanceId();
		bool hitCheck(float x, float y);
		void setPos(float x, float y);
		void changeState(STATE stateNext);
		virtual bool update() override;
		virtual void draw() override;
	};

	class Window : public Task , public MouseClickEvent {
	public:
		enum Constants {
			BUTTONID_EXIT_BUTTON = 1,
		};
		struct ColorProperty {
			unsigned int window;
			unsigned int title;
			unsigned int frame;
		};
	private:
		enum STATE {
			ST_IDLE ,
			ST_DRAG_START ,
			ST_DRAG_MOVE,
			ST_DRAG_END ,
		};
		VECTOR position;
		VECTOR size;
		std::string title;
		ColorProperty colors;
		STATE current;
		STATE next;
		bool isfirst;
		Button* close;
		bool active;
		bool visible;
		MouseEvent mouse;
	public:
		Window();
		~Window();
		bool hitCheck(float x, float y);
		VECTOR getBasePosition();
		void setVisible(bool visible);
		bool isVisible();
		void initialize(VECTOR position, VECTOR size, std::string title);
		virtual bool update() override;
		virtual void draw() override;
		virtual void onClick(Task* sender) override;
		virtual void onUpdate();
		virtual void onDraw();
		virtual void onClickClose();
	};

	//
	// テキスト入力欄
	//
	class TextField : public Task {
	private:
		enum STATE {
			IDLE,
			TEXT_INPUT,
		};
		STATE current;
		STATE next;
		VECTOR pos;
		VECTOR size;
		std::string text;
		int inputHandle;
		bool isPress;
		bool isPress_prev;
		bool isPressTrigger;
		TextFieldEventHandler* eventHandler;
	public:
		TextField(VECTOR pos, VECTOR size, std::string text, TextFieldEventHandler* eventHandler);
		std::string getText();
		bool hitCheck(float x, float y);
		void setPos(float x, float y);
		void setText(std::string text);
		virtual bool update() override;
		virtual void draw() override;
	};
}

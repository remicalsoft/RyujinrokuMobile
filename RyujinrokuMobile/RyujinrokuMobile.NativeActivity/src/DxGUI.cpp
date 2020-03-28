#include"DxGUI.h"

namespace DxGUI {
	MouseEvent::MouseEvent() {
		this->mouseType = MOUSE_INPUT_LEFT;
	}

	void MouseEvent::setMouseType(int mouseType) {
		this->mouseType = mouseType;
	}

	void MouseEvent::update() {
		GetMousePoint(&this->mouseX, &this->mouseY);
		this->mouseVectX = this->mouseX - this->mouseX_prev;
		this->mouseVectY = this->mouseY - this->mouseY_prev;
		this->mouseX_prev = this->mouseX;
		this->mouseY_prev = this->mouseY;
	}

	bool MouseEvent::isPress() {
		return (GetMouseInput() & this->mouseType) != 0;
	}

	int MouseEvent::getMouseVectX() {
		return this->mouseVectX;
	}

	int MouseEvent::getMouseVectY() {
		return this->mouseVectY;
	}

	int MouseEvent::getMousePositionX() {
		return this->mouseX;
	}

	int MouseEvent::getMousePositionY() {
		return this->mouseY;
	}


	//
	// class MouseCursor
	//
	bool MouseCursor::update() {
		return true;
	}

	void MouseCursor::draw(){
		int x = 0;
		int y = 0;
		GetMousePoint(&x, &y);
		DrawCircle(x, y, 5, GetColor(0, 255, 255));
	}


	//
	// class Button
	//
	Button::Button(std::string text, VECTOR pos, VECTOR size, unsigned int color, unsigned int pressColor, MouseClickEvent* eventHandler, int instanceId) {
		this->text = text;
		this->pos = pos;
		this->size = size;
		this->color = color;
		this->pressColor = pressColor;
		this->eventHandler = eventHandler;
		this->instanceId = instanceId;
		this->state = BTNID_IDLE;
		this->stateNext = BTNID_IDLE;
		this->isPress = false;
		this->isPress_prev = false;
		this->isPressTrigger = false;
		this->isHit = false;
		this->isFirst = false;
	}

	void Button::setPos(float x, float y) {
		this->pos = VGet(x, y, 0);
	}

	int Button::getInstanceId() {
		return this->instanceId;
	}

	bool Button::hitCheck(float x, float y) {
		float xMin = this->pos.x;
		float xMax = this->pos.x + this->size.x;
		float yMin = this->pos.y;
		float yMax = this->pos.y + this->size.y;

		if (x >= xMin && x < xMax) {
			if (y >= yMin && y < yMax) {
				return true;
			}
		}
		return false;
	}

	void Button::changeState(STATE stateNext) {
		this->stateNext = stateNext;
	}

	bool Button::update(){
		this->isPress = false;
		this->isHit = false;
		int input = GetMouseInput();
		int isLeft = input & MOUSE_INPUT_LEFT;
		if (isLeft != 0) {
			this->isPress = true;
		}

		this->isPressTrigger = false;
		if (this->isPress != this->isPress_prev) {
			if (this->isPress) {
				this->isPressTrigger = true;
			}
		}
		if (this->isPressTrigger) {
			int mouseX = 0;
			int mouseY = 0;
			GetMousePoint(&mouseX, &mouseY);
			if (hitCheck(mouseX, mouseY)) {
				this->isHit = true;
			}
		}
		this->isPress_prev = this->isPress;

		this->isFirst = false;
		if (this->state != this->stateNext) {
			this->isFirst = true;
		}
		this->state = this->stateNext;
		switch (this->state) {
		case BTNID_IDLE:
			if (this->isHit) {
				this->changeState(BTNID_PRESS);
				if (this->eventHandler) {
					this->eventHandler->onClick(this);
				}
			}
			break;
		case BTNID_PRESS:
			if (!this->isHit) {
				this->changeState(BTNID_IDLE);
				if (this->eventHandler) {
					this->eventHandler->onRelease(this);
				}
			}
			break;
		case BTNID_DISABLE:
			break;
		}

		return true;
	}

	void Button::draw(){
		unsigned int resultColor = this->color;
		switch (this->state) {
		case BTNID_IDLE: resultColor = this->color; break;
		case BTNID_PRESS: resultColor = this->pressColor; break;
		case BTNID_DISABLE: resultColor = this->pressColor; break;
		}
		DrawBox(this->pos.x, this->pos.y, this->pos.x + this->size.x, this->pos.y + this->size.y, resultColor, TRUE);

		int textSizeWidth = 10;
		int textSizeHeight = 20;
		int textX = 0;
		int textY = 0;
		int textWidth = this->text.size() * textSizeWidth;
		int textHeight = textSizeHeight;
		int boxWidth = this->size.x;
		int boxHeight = this->size.y;
		int ofsX = (boxWidth - textWidth) / 2;
		int ofsY = (boxHeight - textHeight) / 2;
		textX = this->pos.x + ofsX;
		textY = this->pos.y + ofsY;

		DrawString(textX, textY, this->text.c_str(), GetColor(255, 255, 255));
	}

	//
	// class Window
	//
	Window::Window() {
		this->initialize(VGet(0, 0, 0), VGet(640, 480, 0), "Empty Window");
	}

	Window::~Window() {
		delete close;
	}

	void Window::initialize(VECTOR position, VECTOR size, std::string title) {
		this->position = position;
		this->size = size;
		this->title = title;
		this->colors.frame = GetColor(32, 32, 32);
		this->colors.title = GetColor(180, 180, 180);
		this->colors.window = GetColor(128, 128, 128);
		this->close = new Button("X", VGet(0, 0, 0), VGet(20, 20, 0), GetColor(40, 40, 40), GetColor(10, 10, 10), this, BUTTONID_EXIT_BUTTON);
		this->active = true;
		this->current = ST_IDLE;
		this->next = ST_IDLE;
		this->isfirst = false;
	}

	void Window::setVisible(bool visible) {
		this->visible = visible;
	}

	bool Window::isVisible() {
		return this->visible;
	}

	bool Window::hitCheck(float x, float y) {
		float xMin = this->position.x;
		float xMax = this->position.x + this->size.x;
		float yMin = this->position.y;
		float yMax = this->position.y + 25;
		if (x >= xMin && x < xMax) {
			if (y >= yMin && y < yMax) {
				return true;
			}
		}
		return false;
	}

	VECTOR Window::getBasePosition() {
		float minX = this->position.x;
		float minY = this->position.y;
		return VGet(minX + 5, minY + 30, 0);
	}

	bool Window::update() {
		this->mouse.update();
		if (!this->isVisible()) {
			return false;
		}
		float minX = this->position.x;
		float minY = this->position.y;
		float maxX = this->position.x + this->size.x;
		float maxY = this->position.y + this->size.y;
		this->close->setPos(maxX - 20 - 4, minY + 4);
		this->close->update();

		this->isfirst = false;
		if (this->current != this->next) {
			this->isfirst = true;
		}
		this->current = this->next;
		switch (this->current) {
			case ST_IDLE:
				{
					int mouseInput = GetMouseInput() & MOUSE_INPUT_LEFT;
					if (mouseInput != 0) {
						if (this->hitCheck(this->mouse.getMousePositionX(), this->mouse.getMousePositionY())) {
							this->next = ST_DRAG_START;
						}
					}
				}
				break;
			case ST_DRAG_START:
				{
					this->next = ST_DRAG_MOVE;
				}
				break;
			case ST_DRAG_MOVE:
				{
					this->position.x += this->mouse.getMouseVectX();
					this->position.y += this->mouse.getMouseVectY();
					int mouseInput = GetMouseInput() & MOUSE_INPUT_LEFT;
					if (mouseInput == 0) {
						this->next = ST_DRAG_END;
					}
				}
				break;
			case ST_DRAG_END:
				{
					this->next = ST_IDLE;
				}
				break;
		}

		this->onUpdate();
		return this->active;
	}

	void Window::draw() {
		if (!this->isVisible()) {
			return;
		}
		float minX = this->position.x;
		float minY = this->position.y;
		float maxX = this->position.x + this->size.x;
		float maxY = this->position.y + this->size.y;

		DrawBox(minX, minY, maxX, maxY, this->colors.frame, TRUE);
		DrawBox(minX + 3, minY + 3, maxX - 3, maxY - 3, this->colors.window, TRUE);
		DrawBox(minX + 3, minY + 3, maxX - 3, minY + 25, this->colors.title, TRUE);
		DrawString(minX + 5, minY + 5, this->title.c_str(), GetColor(0, 0, 0));
		this->close->draw();
		this->onDraw();
	}

	void Window::onUpdate() {
	}

	void Window::onDraw() {
	}

	void Window::onClickClose() {
	}

	void Window::onClick(Task* sender) {
		auto btn = dynamic_cast<Button*>(sender);
		if (btn) {
			if (btn->getInstanceId() == BUTTONID_EXIT_BUTTON) {
				this->active = false;
				this->onClickClose();
			}
		}
	}


	/*
	 *
	 * class TextField
	 *
	 */
	TextField::TextField(VECTOR pos, VECTOR size, std::string text, TextFieldEventHandler* eventHandler) {
		this->pos = pos;
		this->size = size;
		this->text = text;
		this->inputHandle = MakeKeyInput(30, FALSE, FALSE, FALSE);
		this->current = IDLE;
		this->next = IDLE;
		this->isPress = false;
		this->isPress_prev = false;
		this->isPressTrigger = false;
		this->size.y = 30;
		this->eventHandler = eventHandler;
	}

	std::string TextField::getText() {
		return this->text;
	}

	void TextField::setText(std::string text) {
		this->text = text;
	}

	bool TextField::hitCheck(float x, float y) {
		float xMin = this->pos.x;
		float xMax = this->pos.x + this->size.x;
		float yMin = this->pos.y;
		float yMax = this->pos.y + this->size.y;
		if (x >= xMin && x < xMax) {
			if (y >= yMin && y < yMax) {
				return true;
			}
		}
		return false;
	}

	void TextField::setPos(float x, float y) {
		this->pos = VGet(x, y, 0);
	}

	/* virtual */
	bool TextField::update() {
		float minX = this->pos.x;
		float minY = this->pos.y;
		float maxX = this->pos.x + this->size.x;
		float maxY = this->pos.y + this->size.y;
		int input = GetMouseInput();
		int isLeft = input & MOUSE_INPUT_LEFT;
		this->isPress = false;
		if (isLeft != 0) {
			this->isPress = true;
		}
		this->isPressTrigger = false;
		if (this->isPress != this->isPress_prev) {
			if (this->isPress) {
				this->isPressTrigger = true;
			}
		}

		bool isfirst = false;
		if (this->current != this->next) {
			isfirst = true;
		}
		this->current = this->next;
		switch (this->current) {
		case IDLE:
			if (this->isPressTrigger) {
				int mouseX = 0;
				int mouseY = 0;
				GetMousePoint(&mouseX, &mouseY);
				if (this->hitCheck(mouseX, mouseY)) {
					this->next = TEXT_INPUT;
				}
			}
			break;
		case TEXT_INPUT:
			if (isfirst) {
				SetActiveKeyInput(this->inputHandle);
				SetKeyInputString(this->text.c_str(), this->inputHandle);
			}
			if (CheckKeyInput(this->inputHandle) != 0) {
				this->next = IDLE;
				char buf[32];
				GetKeyInputString(buf, this->inputHandle);
				this->text = buf;
				if (this->eventHandler) {
					this->eventHandler->onTextInputComplete(this);
				}
			}
			break;
		}

		this->isPress_prev = this->isPress;
		return true;
	}

	/* TextField::virtual */
	void TextField::draw() {
		DrawBox(this->pos.x, this->pos.y, this->pos.x + this->size.x, this->pos.y + this->size.y, GetColor(64, 64, 64), TRUE);
		switch (this->current) {
		case IDLE:
			{
				DrawString(this->pos.x + 3, this->pos.y + 5, this->text.c_str(), GetColor(0, 0, 0));
			}
			break;
		case TEXT_INPUT:
			{
				// 入力モードを描画
				DrawKeyInputModeString(640, 480);
				// 入力途中の文字列を描画
				DrawKeyInputString(this->pos.x + 3, this->pos.y + 5, this->inputHandle);
			}
			break;
		}

	}
}

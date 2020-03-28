#include "InspectorView.h"
#include "Keyboard.h"
#include "SpriteRendererReference.h"
#include "MV1ModelReference.h"

namespace Editor {
	//
	// class InspectorView
	//
	void InspectorView::setRef(Object* ref) {
		this->ref = ref;
		if (this->referenceView) {
			delete this->referenceView;
			this->referenceView = NULL;
		}

		if (this->ref) {
			this->textField->setText(this->ref->getName());
			if (dynamic_cast<SpriteRenderer*>(this->ref) != NULL) {
				this->referenceView = new SpriteRendererReference(this);
			}
			else if (dynamic_cast<MV1Renderer*>(this->ref) != NULL) {
				this->referenceView = new MV1ModelReference(this);
			}
		}
	}

	Object* InspectorView::getRef() {
		return this->ref;
	}

	InspectorView::InspectorView(VECTOR pos) {
		this->initialize(pos, VGet(350, 800, 0), "Inspector");
		this->ref = NULL;
		this->editMode = Position;
		this->textField = new DxGUI::TextField(VGet(0, 0, 0), VGet(120, 30, 0), "GameObject", this);
		this->referenceView = NULL;
	}

	InspectorView::~InspectorView() {
		delete this->textField;
		if (this->referenceView) {
			delete this->referenceView;
		}
	}

	bool InspectorView::keyOk(int key) {
		if (key == 1) return true;
		if (key > 30) return true;
		return false;
	}

	// virtual
	void InspectorView::onUpdate() {
		this->mouse.update();
		if (!this->ref) {
			return;
		}
		auto key = Keyboard::getIns();
		auto key7 = key->getPressingCount(KEY_INPUT_7);
		auto key8 = key->getPressingCount(KEY_INPUT_8);
		auto key9 = key->getPressingCount(KEY_INPUT_9);
		auto key0 = key->getPressingCount(KEY_INPUT_0);
		auto keyK = key->getPressingCount(KEY_INPUT_K);
		auto keyL = key->getPressingCount(KEY_INPUT_L);
		auto keyLShift = key->getPressingCount(KEY_INPUT_LSHIFT);

		if (key7 == 1) {
			this->editMode = Position;
		}
		if (key8 == 1) {
			this->editMode = Angle;
		}
		if (key9 == 1) {
			this->editMode = Scale;
		}

		switch (this->editMode) {
		case Position:
		{
			auto z = key->getPressingCount(KEY_INPUT_Z);
			auto up = key->getPressingCount(KEY_INPUT_UP);
			auto right = key->getPressingCount(KEY_INPUT_RIGHT);
			auto down = key->getPressingCount(KEY_INPUT_DOWN);
			auto left = key->getPressingCount(KEY_INPUT_LEFT);
			auto pos = ref->getPos();
			float addVal = 1.0f;
			if (z == 0) {
				if (keyOk(up)) { pos.y += addVal; }
				if (keyOk(right)) { pos.x += addVal; }
				if (keyOk(down)) { pos.y -= addVal; }
				if (keyOk(left)) { pos.x -= addVal; }
			}
			if (z > 0) {
				if (keyOk(right)) { pos.z += addVal; }
				if (keyOk(left)) { pos.z -= addVal; }
			}
			if (keyLShift > 0) {
				if (mouse.isPress()) {
					int vx = mouse.getMouseVectX();
					int vy = mouse.getMouseVectY();
					pos.x += vx;
					pos.y -= vy;
				}
			}

			this->ref->setPos(pos);
		}
		break;
		case Angle:
		{
			auto z = key->getPressingCount(KEY_INPUT_Z);
			auto up = key->getPressingCount(KEY_INPUT_UP);
			auto right = key->getPressingCount(KEY_INPUT_RIGHT);
			auto down = key->getPressingCount(KEY_INPUT_DOWN);
			auto left = key->getPressingCount(KEY_INPUT_LEFT);
			auto angle = ref->getAngle();
			auto addAngle = 3.14f / 120.0f;
			float addVal = addAngle;
			if (z == 0) {
				if (keyOk(up)) { angle.y += addVal; }
				if (keyOk(right)) { angle.x += addVal; }
				if (keyOk(down)) { angle.y -= addVal; }
				if (keyOk(left)) { angle.x -= addVal; }
			}
			if (z > 0) {
				if (keyOk(right)) { angle.z += addVal; }
				if (keyOk(left)) { angle.z -= addVal; }
			}
			this->ref->setAngle(angle);
		}
		break;
		case Scale:
		{
			auto z = key->getPressingCount(KEY_INPUT_Z);
			auto up = key->getPressingCount(KEY_INPUT_UP);
			auto right = key->getPressingCount(KEY_INPUT_RIGHT);
			auto down = key->getPressingCount(KEY_INPUT_DOWN);
			auto left = key->getPressingCount(KEY_INPUT_LEFT);
			auto scale = ref->getScale();
			auto addScale = 1 / 120.0f;
			float addVal = addScale;

			if (z == 0) {
				if (keyOk(up)) { scale.y += addVal; }
				if (keyOk(right)) { scale.x += addVal; }
				if (keyOk(down)) { scale.y -= addVal; }
				if (keyOk(left)) { scale.x -= addVal; }
			}
			if (z > 0) {
				if (keyOk(right)) { scale.z += addVal; }
				if (keyOk(left)) { scale.z -= addVal; }
			}
			this->ref->setScale(scale);
		}
		break;
		}

		this->textField->update();
		if (this->referenceView) {
			this->referenceView->onUpdate();
		}
	}

	// virtual
	void InspectorView::onDraw() {
		auto pos = VGet(0, 0, 0);
		auto angle = VGet(0, 0, 0);
		auto scale = VGet(0, 0, 0);
		int objectId = 0;
		if (ref) {
			pos = ref->getPos();
			angle = ref->getAngle();
			scale = ref->getScale();
			objectId = ref->getObjectId();
		}
		auto fontColor = GetColor(0, 0, 0);
		auto color1 = fontColor;
		auto color2 = fontColor;
		auto color3 = fontColor;
		auto viewPos = this->getBasePosition();
		switch (this->editMode) {
			case Position : color1 = GetColor(255, 255, 0); break;
			case Angle    : color2 = GetColor(255, 255, 0); break;
			case Scale    : color3 = GetColor(255, 255, 0); break;
		}
		DrawFormatString(viewPos.x + 10, viewPos.y +  10, fontColor, "[Object]");
		DrawFormatString(viewPos.x + 10, viewPos.y +  30, fontColor, "objectId %d", objectId);
		DrawFormatString(viewPos.x + 10, viewPos.y +  50, fontColor, "position x:%0.2f,y:%0.2f,z:%0.2f", pos.x, pos.y, pos.z);
		DrawFormatString(viewPos.x + 10, viewPos.y +  70, fontColor, "angle    x:%0.2f,y:%0.2f,z:%0.2f", angle.x, angle.y, angle.z);
		DrawFormatString(viewPos.x + 10, viewPos.y +  90, fontColor, "scale    x:%0.2f,y:%0.2f,z:%0.2f", scale.x, scale.y, scale.z);
		DrawFormatString(viewPos.x + 10, viewPos.y + 110,    color1, "7:Position");
		DrawFormatString(viewPos.x + 10, viewPos.y + 130,    color2, "8:Angle");
		DrawFormatString(viewPos.x + 10, viewPos.y + 150,    color3, "9:Scale");
		this->textField->setPos(viewPos.x + 10, viewPos.y + 180);
		this->textField->draw();
		if (this->referenceView) {
			this->referenceView->onDraw();
		}
	}

	// virtual
	void InspectorView::onClick(Task* sender) {
		DxGUI::Window::onClick(sender);
	}

	// virtual
	void InspectorView::onClickClose() {
		this->setVisible(false);
	}

	// virtual
	void InspectorView::onTextInputComplete(Task* sender) {
		auto textField = dynamic_cast<DxGUI::TextField*>(sender);
		if (textField) {
			this->ref->setName(textField->getText());
		}
	}
}
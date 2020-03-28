#include "CameraInspectorView.h"
#include "Keyboard.h"
#include <DxLib.h>


namespace Editor {
	//
	// class CameraInspectorView
	//
	CameraInspectorView::CameraInspectorView(VECTOR pos) {
		this->initialize(pos, VGet(350, 800, 0), "Camera Inspector");
		this->ref = NULL;
		this->editMode = EditCameraPosition;
		this->Lmouse.setMouseType(MOUSE_INPUT_LEFT);
		this->switchBtn = new DxGUI::Button("Change", VGet(0, 0, 0), VGet(150, 30, 0), GetColor(64, 64, 64), GetColor(32, 32, 32), this, BUTTONID_SWITCH);
		this->resetBtn = new DxGUI::Button("Reset", VGet(0, 0, 0), VGet(150, 30, 0), GetColor(64, 64, 64), GetColor(32, 32, 32), this, BUTTONID_RESET);
	}

	CameraInspectorView::~CameraInspectorView() {
		delete this->switchBtn;
		delete this->resetBtn;
	}

	void CameraInspectorView::setFocus(Camera* ref) {
		this->ref = ref;
	}

	bool CameraInspectorView::keyOk(int key) {
		if (key == 1)return true;
		if (key > 30)return true;
		return false;
	}

	// virtual
	void CameraInspectorView::onUpdate() {
		this->Lmouse.update();
		auto key = Keyboard::getIns();
		auto z = key->getPressingCount(KEY_INPUT_Z);
		auto up = key->getPressingCount(KEY_INPUT_UP);
		auto right = key->getPressingCount(KEY_INPUT_RIGHT);
		auto down = key->getPressingCount(KEY_INPUT_DOWN);
		auto left = key->getPressingCount(KEY_INPUT_LEFT);
		auto keyLShift = key->getPressingCount(KEY_INPUT_LSHIFT);
		VECTOR pos = VGet(0, 0, 0);
		float V = 0;
		float H = 0;
		float T = 0;
		if (this->ref) {
			pos = this->ref->getPos();
			V = this->ref->getV();
			H = this->ref->getH();
			T = this->ref->getT();
		}

		if (this->editMode == EditCameraPosition) {
			if (z == 0) {
				if (keyOk(up)) { pos.y += 1; }
				if (keyOk(right)) { pos.x += 1; }
				if (keyOk(down)) { pos.y -= 1; }
				if (keyOk(left)) { pos.x -= 1; }
			}
			if (z > 0) {
				if (keyOk(right)) { pos.z += 1; }
				if (keyOk(left)) { pos.z -= 1; }
			}
			if (keyLShift > 0) {
				if (Lmouse.isPress()) {
					if (z == 0) {
						int vx = Lmouse.getMouseVectX();
						int vy = Lmouse.getMouseVectY();
						pos.x += vx;
						pos.y -= vy;
					}
					if (z > 0) {
						int vz = Lmouse.getMouseVectY();
						pos.z += vz;
					}
				}
			}
		}
		if (this->editMode == EditAngle) {
			float addAngle = 3.14f / 240.0f;
			float addVal = addAngle;
			if (z == 0) {
				if (keyOk(up)) { V += addVal; }
				if (keyOk(right)) { H += addVal; }
				if (keyOk(down)) { V -= addVal; }
				if (keyOk(left)) { H -= addVal; }
			}
			if (z > 0) {
				if (keyOk(right)) { T += addVal; }
				if (keyOk(left)) { T -= addVal; }
			}
			if (keyLShift > 0) {
				if (Lmouse.isPress()) {
					if (z == 0) {
						float vx = 0;
						float vy = 0;
						if (Lmouse.getMouseVectX() > 0) { vx = 1 * addVal; }
						if (Lmouse.getMouseVectX() < 0) { vx = -1 * addVal; }
						if (Lmouse.getMouseVectY() > 0) { vy = 1 * addVal; }
						if (Lmouse.getMouseVectY() < 0) { vy = -1 * addVal; }
						H += vx;
						V -= vy;
					}
					if (z > 0) {
						float vz = 0;
						if (Lmouse.getMouseVectY() > 0) { vz = 1 * addVal; }
						if (Lmouse.getMouseVectY() < 0) { vz = -1 * addVal; }
						T += vz;
					}
				}
			}
		}

		auto viewPos = this->getBasePosition();
		this->switchBtn->setPos(viewPos.x + 10, viewPos.y + 100);
		this->resetBtn->setPos(viewPos.x + 10, viewPos.y + 140);
		this->switchBtn->update();
		this->resetBtn->update();
		if (this->ref) {
			this->ref->setPos(pos.x, pos.y, pos.z);
			this->ref->setVHT(V, H, T);
		}
	}

	// virtual
	void CameraInspectorView::onDraw() {
		auto viewPos = this->getBasePosition();
		auto fontColor = GetColor(0, 0, 0);
		VECTOR pos = VGet(0, 0, 0);
		float V = 0;
		float H = 0;
		float T = 0;
		if (this->ref) {
			pos = this->ref->getPos();
			V = this->ref->getV();
			H = this->ref->getH();
			T = this->ref->getT();
		}

		DrawFormatString(viewPos.x + 10, viewPos.y + 10, fontColor, "[Camera]");
		DrawFormatString(viewPos.x + 10, viewPos.y + 30, fontColor, "position x:%0.2f,y:%0.2f,z:%0.2f", pos.x, pos.y, pos.z);
		DrawFormatString(viewPos.x + 10, viewPos.y + 50, fontColor, "VHT      V:%0.2f,H:%0.2f,T:%0.2f", V, H, T);
		const char* modeText = "";
		switch (this->editMode) {
		case EditCameraPosition: modeText = "カメラ座標モード"; break;
		case EditAngle: modeText = "角度調整モード"; break;
		}
		DrawFormatString(viewPos.x + 10, viewPos.y + 200, fontColor, modeText);
		this->switchBtn->draw();
		this->resetBtn->draw();
	}

	// virtual
	void CameraInspectorView::onClickClose() {
		this->setVisible(false);
	}

	// virtual 
	void CameraInspectorView::onClick(Task* sender) {
		DxGUI::Window::onClick(sender);
		auto btn = dynamic_cast<DxGUI::Button*>(sender);
		if (btn) {
			if (btn->getInstanceId() == BUTTONID_SWITCH) {
				switch (this->editMode) {
				case EditCameraPosition: this->editMode = EditAngle; break;
				case EditAngle: this->editMode = EditCameraPosition; break;
				}
			}
			if (btn->getInstanceId() == BUTTONID_RESET) {
				if (this->ref) {
					this->ref->reset();
				}
			}
		}
	}
}
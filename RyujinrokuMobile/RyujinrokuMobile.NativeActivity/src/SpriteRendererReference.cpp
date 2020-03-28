#include "SpriteRendererReference.h"

//
// class SpriteRendererReference
//
namespace Editor {
	SpriteRendererReference::SpriteRendererReference(InspectorView* view) : InspectorView::ReferenceView(view) {
		this->transBtn = new DxGUI::Button("Trans", VGet(0, 0, 0), VGet(60, 30, 0), GetColor(64, 64, 64), GetColor(32, 32, 32), this, BUTTONID_TRANS_FLAG);
	}

	SpriteRendererReference::~SpriteRendererReference() {
		delete this->transBtn;
	}

	// virtual
	void SpriteRendererReference::onUpdate() {
		this->transBtn->update();
	}

	// virtual
	void SpriteRendererReference::onDraw() {
		auto inspector = this->getInspector();
		auto viewPos = inspector->getBasePosition();
		auto ref = dynamic_cast<SpriteRenderer*>(inspector->getRef());
		auto fontColor = GetColor(0, 0, 0);
		const char* transFlagText = "";
		if (ref) {
			transFlagText = ref->isTrans() ? "ON" : "OFF";
		}
		DrawFormatString(viewPos.x + 100, viewPos.y + 225, fontColor, "TransFlag:%s", transFlagText);
		this->transBtn->setPos(viewPos.x + 10, viewPos.y + 220);
		this->transBtn->draw();
	}

	// virtual
	void SpriteRendererReference::onClick(Task* sender) {
		DxGUI::MouseClickEvent::onClick(sender);
		auto inspector = this->getInspector();
		auto ref = dynamic_cast<SpriteRenderer*>(inspector->getRef());
		if (!ref) {
			return;
		}
		auto btn = dynamic_cast<DxGUI::Button*>(sender);
		if (!btn) {
			return;
		}
		if (btn->getInstanceId() == BUTTONID_TRANS_FLAG) {
			ref->setTrans(ref->isTrans() ? FALSE : TRUE);
		}
	}
}
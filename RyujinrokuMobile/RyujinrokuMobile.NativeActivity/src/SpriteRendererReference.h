#pragma once
#include "InspectorView.h"

namespace Editor {
	class SpriteRendererReference : public InspectorView::ReferenceView, public DxGUI::MouseClickEvent {
	private:
		enum BUTTON_ID {
			BUTTONID_TRANS_FLAG = 1000,
		};
		DxGUI::Button* transBtn;
	public:
		SpriteRendererReference(InspectorView* view);
		~SpriteRendererReference();
		virtual void onUpdate() override;
		virtual void onDraw() override;
		virtual void onClick(Task* sender) override;
	};
}
#pragma once
#include "InspectorView.h"

namespace Editor {
	class MV1ModelReference : public InspectorView::ReferenceView, public DxGUI::MouseClickEvent {
	private:
	public:
		MV1ModelReference(InspectorView* view);
		~MV1ModelReference();
		virtual void onUpdate() override;
		virtual void onDraw() override;
		virtual void onClick(Task* sender) override;
	};
}
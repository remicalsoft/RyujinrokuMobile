#pragma once
#include "DxGUI.h"
#include "SpriteRenderer.h"

namespace Editor {
	//
	// オブジェクト監視ウィンドウ
	// オブジェクトの座標・角度・スケール率などの操作を行える。
	// 参照するテクスチャなどもここで操作出来たら・・・
	//
	class InspectorView : public DxGUI::Window, public DxGUI::TextFieldEventHandler {
	public:
		class ReferenceView {
		private:
			InspectorView* view;
		protected :
			InspectorView* getInspector() {
				return this->view;
			}
		public:
			ReferenceView(InspectorView* view) {
				this->view = view;
			}
			virtual void onUpdate() {
			}
			virtual void onDraw() {
			}
		};
	private:
		enum EditMode {
			Position,
			Angle,
			Scale,
		};

		Object* ref;
		EditMode editMode;
		DxGUI::MouseEvent mouse;
		DxGUI::TextField* textField;
		ReferenceView* referenceView;
	public:
		void setRef(Object* ref);
		Object* getRef();
		InspectorView(VECTOR pos);
		~InspectorView();
		bool keyOk(int key);
		virtual void onUpdate();
		virtual void onDraw();
		virtual void onClick(Task* sender);
		virtual void onClickClose();
		virtual void onTextInputComplete(Task* sender);
	};
}
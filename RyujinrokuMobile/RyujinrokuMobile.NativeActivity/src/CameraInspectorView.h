#pragma once
#include "DxGUI.h"
#include "Camera.h"

namespace Editor {
	//
	// カメラ設定監視ウィンドウ
	// カメラの編集や座標、角度の状態を表示したりする。
	//
	class CameraInspectorView : public DxGUI::Window {
	private:
		enum BUTON_ID {
			BUTTONID_SWITCH = 1000,
			BUTTONID_RESET = 1001,
		};
		enum EditMode {
			EditCameraPosition,
			EditAngle,
		};
		EditMode editMode;
		Camera* ref;
		DxGUI::MouseEvent Lmouse;
		DxGUI::Button* switchBtn;
		DxGUI::Button* resetBtn;
	public:
		CameraInspectorView(VECTOR pos);
		~CameraInspectorView();
		void setFocus(Camera* ref);
		bool keyOk(int key);
		virtual void onUpdate();
		virtual void onDraw();
		virtual void onClickClose();
		virtual void onClick(Task* sender);
	};
}
#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"
#include "Keyboard.h"
#include "Pad.h"
#include "Toast.h"
#include <string>
#include "Utils.h"
#include "../SettingApp/Setting/ConfigData.h"
#include "Image.h"
#include "ImageBullet.h"
#include "SavedData.h"
#include "SavedBarrageData.h"
#include "SE.h"
#include "BGM.h"
#include "TotalPlayTime.h"

using namespace std;

/*!
	@brief ソフトウェアのInitialize
*/
SystemMain::SystemMain() : _isErr(false)
{
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できる
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetWindowText("四聖龍神録2");
	{
		string pathS = Utils::getSavePath();
		pathS += "SavedData";
		if (!Utils::existsFolder(pathS.c_str())) {
			CreateDirectory(pathS.c_str(), NULL);
		}

	}
	int isFullScreen = -1;
	
	D_ConfigData *data = ConfigData::read();
    data->windowMode = WindowMode_Window;
	switch (data->windowMode) {
	case 	WindowMode_Ask:
		isFullScreen = MessageBox(NULL, TEXT("フルスクリーンモードで起動しますか？\n\n(ウィンドウサイズは自由に変更可能です)\n"), TEXT("スクリーン設定"), MB_YESNO | MB_ICONQUESTION);
		if (isFullScreen != IDYES){
			ChangeWindowMode(TRUE);//ウィンドウモードに変更
		}
		break;
	case 	WindowMode_Full:
		break;
	case 	WindowMode_Window:
		ChangeWindowMode(TRUE);//ウィンドウモードに変更
		break;
	case 	WindowMode_Small:
		ChangeWindowMode(TRUE);//ウィンドウモードに変更
		SetWindowSizeExtendRate(0.5);
		break;
	}

	SetGraphMode(WIN_W, WIN_H, COLOR_BIT);

	if (DxLib_Init()) {
		_isErr = true;
		return;
	}
	SetDXArchiveKeyString("monmondaidai");
	SetDrawScreen(DX_SCREEN_BACK);

	Image::getIns()->load();
	ImageBullet::getIns()->load();
	SavedData::getIns()->load();
	SavedBarrageData::getIns()->load();

	SE::getIns()->load(data->seVolume);
	BGM::getIns()->setVolume(data->bgmVolume);

	delete data;
}

SystemMain::~SystemMain()
{
	DxLib_End();
}

void SystemMain::main() {
	if (_isErr) {
		return;
	}
	Looper *looper = new Looper();
	while (!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()) {
		Keyboard::getIns()->update();
		Pad::getIns()->update();
		TotalPlayTime::getIns()->update();
		if (!looper->main()) {
			break;
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DELETE) == 1) {
			clsDx();
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_F12) == 1) {
			break;
		}
	}
	SavedData::getIns()->save();
	SavedBarrageData::getIns()->save();
	D_ConfigData *data = ConfigData::read();
	if (data->moveHP && 0) {
		MessageBox(NULL, TEXT("よければ一言、掲示板に感想をお寄せください\nこれは設定でオフにできます"), TEXT("HPに移動します"), MB_OK);
		//		ShellExecute(NULL, NULL, "http://dixq.net/forum/viewforum.php?f=112", NULL, NULL, SW_SHOWNORMAL);
		ShellExecute(NULL, NULL, "http://dixq.net/ryujin2/", NULL, NULL, SW_SHOWNORMAL);
	
	}
	delete data;
	delete looper;
}

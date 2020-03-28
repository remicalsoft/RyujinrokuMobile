#include "DxLib.h"
#include "ConfigScene.h"
#include "Define.h"
#include "SE.h"
#include "Utils.h"
#include "DebugMode.h"
#include "Keyboard.h"

#define NUM (PAD_TYPE_NUM-4+1)

const static int FINISH_COUNT = 64;

// 起動時実行
ConfigScene::ConfigScene(ISceneChangedListener *impl, ScenePrmBase* prm) : Scene(impl) {
	_configStep = 0;
	_isCanceled = false;
	_counter = 0;
	_cancelCounter = 0;
	_fontA = CreateFontToHandle(FONT, 24, 4, DX_FONTTYPE_ANTIALIASING_4X4);
	_fontB = CreateFontToHandle(FONT, 16, 4, DX_FONTTYPE_ANTIALIASING_4X4);
	_colorFocus = GetColor(255, 255, 255);
	_colorOther = GetColor(50, 50, 50);
	_colorFront = GetColor(255, 0, 255);
	_colorBack = GetColor(0, 0, 0);
	_imgBack = LoadGraph("dat/image/menu/back_dark.jpg");
	_imgTitle = LoadGraph("dat/image/config/title.png");
	_imgConfig = LoadGraph("dat/image/config/keyconfig.png");

//	Pad::getIns()->inputPadData(_pad_dum);
	_pad_dum = Pad::getIns()->getPadData();
	memset(_xFlag, 0, sizeof(int) * 6);
	_debugCommandStatus = 0;
}


// 退場時実行
ConfigScene::~ConfigScene() {

	DeleteGraph(_imgBack);
	DeleteGraph(_imgTitle);
	DeleteGraph(_imgConfig);
	DeleteFontToHandle(_fontA);
	DeleteFontToHandle(_fontB);

}

// コンフィグが最後まで行ったらセーブ
void ConfigScene::saveConfig() {
	// (´・ω・｀)
//	Pad::getIns()->registPadData(_pad_dum);
	Pad::getIns()->setPadData(_pad_dum);
	Pad::getIns()->save();
	_isCanceled = true;
}

// 描写専用
void ConfigScene::draw() {

	int color;
	int fade;
	bool isBrended = false;
	char numstr[32];
	char *keyname[] = {
		"LEFT","UP","RIGHT","DOWN","ショット","ボム","低速移動","スタート","ドレス"
	};

	bool colorflag[PAD_MAX-4] = { true, false };

	for (int i = 0; i<PAD_MAX-4; i++) {

		if (i == _configStep) {
			colorflag[i] = true;
			if (_xFlag[i]<20)	_xFlag[i] += 4;
		}
		else {
			colorflag[i] = false;
			if (_xFlag[i]>0)		_xFlag[i] -= 4;
		}

	}


	DrawGraph(0, 0, _imgBack, TRUE);
	DrawGraph((1280 - 298) / 2, 100, _imgTitle, TRUE);
	DrawGraph(600, 250, _imgConfig, TRUE);

	for (int i = 4; i < PAD_TYPE_NUM; i++) {
//		sprintf_s(numstr, "%02d",_pad_dum[i]);
		sprintf_s(numstr, "%02d",_pad_dum.padArray[i]);
		color = (i == _configStep+4) ? _colorFocus : _colorOther;
		DrawStringToHandle( 160, 263 + 70 * (i-4), keyname[i], color, _fontA);
		fade = 255 * _xFlag[i-4] / 20;
		DrawBox(300, 240 + 70 * (i - 4), 450, 303 + 70 * (i - 4), GetColor(0, 0, 0), TRUE);
		DrawBox(305, 245 + 70 * (i - 4), 445, 298 + 70 * (i - 4), GetColor(fade, 0, fade), TRUE);
		DrawStringToHandle( 360, 260 + 70 * (i-4), numstr, color, _fontA);
	}
	color = (_configStep==NUM-1) ? _colorFocus : _colorOther;
	DrawStringToHandle(165, 260+70*(PAD_TYPE_NUM - 4), "Exit", color, _fontA);

	color = _colorFocus;
	DrawFormatStringToHandle(150, 680, color, _fontB, "※パッドのボタンを押すと、選択中のカテゴリに応じて");
	DrawFormatStringToHandle(150, 710, color, _fontB, "　キーコンフィグが自動でなされます。");
	DrawFormatStringToHandle(150, 740, color, _fontB, "　Exitに合わせて、Ｚキーを押すと確定、");
	DrawFormatStringToHandle(150, 770, color, _fontB, "　Ｘキーを押すとキャンセルになります。");


	if (_counter < 32) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - _counter * 8);
		isBrended = true;
	}
	if (_cancelCounter > 16) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_cancelCounter - 16) * 16);
		isBrended = true;
	}
	if (isBrended) {
		DrawBox(0, 0, WIN_W, WIN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

// 計算専用
bool ConfigScene::update() {

	int dum;
	_counter++;

	updateDebugCommand();

	if (!_isCanceled) {

		int i, dum, PadInput, mul = 1;
		PadInput = GetJoypadInputState(DX_INPUT_PAD1);//パッドの入力状態を取得
		for (i = 0; i<PAD_MAX; i++) {
			if (PadInput & mul)  _count[i]++;
			else                 _count[i] = 0;
			mul *= 2;
			if (_count[i] == 1) {
				if (i > 3 && _configStep != NUM - 1) {
					dum = _pad_dum.padArray[_configStep+4];
					_pad_dum.padArray[_configStep+4] = i;
					for (int k = 4; k < PAD_TYPE_NUM; k++) {	// 重複割り当てを回避
						if (k == _configStep+4)	continue;
						if (_pad_dum.padArray[k] == _pad_dum.padArray[_configStep+4])	_pad_dum.padArray[k] = dum;
					}
					_configStep = (_configStep + 1) % NUM;
					SE::getIns()->setPlay(eSE::eSE_upDown);
				}
			}
		}

		if (Utils::isKeyPushed(ePad::down)) {
			SE::getIns()->setPlay(eSE::eSE_upDown);
			_configStep = ( _configStep + 1) % NUM;
		}
		if (Utils::isKeyPushed(ePad::up)) {
			SE::getIns()->setPlay(eSE::eSE_upDown);
			_configStep = (_configStep + (NUM - 1)) % NUM;
		}
		if (_configStep == NUM - 1) {
			if (CheckHitKey(KEY_INPUT_X) == 1)	// Xキーでキャンセル
			{
				SE::getIns()->setPlay(eSE::eSE_cancel);
				_isCanceled = true;
			}
			if (CheckHitKey(KEY_INPUT_Z) == 1)	// Zキーでセーブ
			{
				SE::getIns()->setPlay(eSE::eSE_select);
				saveConfig();
				_isCanceled = true;
			}
		}
	}

	if (_isCanceled) {
		_cancelCounter++;
	}
	if (_cancelCounter == FINISH_COUNT/2) {
		_implSceneChanged->onSceneChanged(eScene::SceneDelete, true, NULL);
		return false;
	}

	return true;
}

void ConfigScene::updateDebugCommand()
{
	const static int N = 8;
	//"ETnatu17"
	char key[256];
	GetHitKeyStateAll(key);

	char password[N] = {
		KEY_INPUT_E,
		KEY_INPUT_T,
		KEY_INPUT_N,
		KEY_INPUT_A,
		KEY_INPUT_T,
		KEY_INPUT_U,
		KEY_INPUT_1,
		KEY_INPUT_7,
	};
	for (int i = 0; i<256; i++) {
		if (i == password[_debugCommandStatus]) {
			continue;
		}
		if (Keyboard::getIns()->getPressingCount(i) == 1) {
			_debugCommandStatus = 0;
			break;
		}
	}
	if (Keyboard::getIns()->getPressingCount(password[_debugCommandStatus]) == 1) {
		_debugCommandStatus++;
		if (_debugCommandStatus == N) {
			DebugMode::getIns()->isUnlocked = true;
			PlaySound("dat/sound/menu/bought.wav", DX_PLAYTYPE_BACK);
			_debugCommandStatus = 0;
		}
	}

}

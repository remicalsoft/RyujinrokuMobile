#include "Keyboard.h"
#include <DxLib.h>

Keyboard::Keyboard() {
	memset(_keyPressingCount,  0, sizeof(_keyPressingCount));
	memset(_keyReleasingCount, 0, sizeof(_keyReleasingCount));
}

//更新
bool Keyboard::update() {
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);       //今のキーの入力状態を取得
	for (int i = 0; i<KEY_NUM; i++) {
		if (nowKeyStatus[i] != 0) {            //i番のキーが押されていたら
			if (_keyReleasingCount[i] > 0) {//離されカウンタが0より大きければ
				_keyReleasingCount[i] = 0;   //0に戻す
			}
			_keyPressingCount[i]++;          //押されカウンタを増やす
		}
		else {                             //i番のキーが離されていたら
			if (_keyPressingCount[i] > 0) { //押されカウンタが0より大きければ
				_keyPressingCount[i] = 0;    //0に戻す
			}
			_keyReleasingCount[i]++;         //離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int Keyboard::getPressingCount(int keyCode) {
	if (!Keyboard::isAvailableCode(keyCode)) {
		return -1;
	}
	return _keyPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int Keyboard::getReleasingCount(int keyCode) {
	if (!Keyboard::isAvailableCode(keyCode)) {
		return -1;
	}
	return _keyReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool Keyboard::isAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode<KEY_NUM)) {
		return false;
	}
	return true;
}

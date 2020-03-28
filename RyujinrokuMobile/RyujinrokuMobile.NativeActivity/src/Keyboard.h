#pragma once

#include "Singleton.h"

class Keyboard : public Singleton<Keyboard> {

	Keyboard();
	friend Singleton< Keyboard >;

public:
	bool update();	//更新
	int getPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
	int getReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得

private:
	static const int KEY_NUM = 256;	//キー総数
	int _keyPressingCount[KEY_NUM];//押されカウンタ
	int _keyReleasingCount[KEY_NUM];//離されカウンタ

	bool isAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う
};

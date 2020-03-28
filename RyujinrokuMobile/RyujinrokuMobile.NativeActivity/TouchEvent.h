#pragma once

#include "Singleton.h"
#include "Pos.h"

class TouchEvent final : public Singleton<TouchEvent> {

public:
	TouchEvent() = default;
	void update();
	const Pos getPos(int id) const;  //eIDのボタンの入力状態を取得

private:
	Pos _pos[2];	//タッチしている指の座標
	int _touchNum;	//タッチしている指の数
};

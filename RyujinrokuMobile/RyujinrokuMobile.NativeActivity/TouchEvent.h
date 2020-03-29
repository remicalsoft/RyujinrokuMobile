#pragma once

#include "Singleton.h"
#include "Pos.h"
#include <array>
#include <list>

class TouchEvent final : public Singleton<TouchEvent> {

public:
	TouchEvent() {
		_pos.   fill(Pos(-1, -1));
		_prePos.fill(Pos(-1, -1));
	}
	void update();
	Pos getPos   (int id) const;  //eIDのボタンの入力状態を取得
	Pos getPrePos(int id) const;
	int getPressingCount(int id) const {
		return _pressingCount[id];
	}
	int getReleasingCount(int id) const {
		return _releasingCount[id];
	}
private:
	std::array<Pos, 2> _pos;	//タッチしている指の座標
	std::array<Pos, 2> _prePos;	//タッチしている指の座標
	std::list<Pos> _history;	//座標の履歴
	int _touchNum;	//タッチしている指の数
	std::array<int,2> _pressingCount;	//押しているフレーム数
	std::array<int,2> _releasingCount;	//離しているフレーム数
	float _speed, _angle; //指1が動いている速さと向き

	static const int HISTORY_MAX = 60;
};

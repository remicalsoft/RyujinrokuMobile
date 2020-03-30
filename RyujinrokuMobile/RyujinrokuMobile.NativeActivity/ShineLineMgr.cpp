#include "ShineLineMgr.h"
#include "Define.h"
#include <DxLib.h>
#include "ShineLineIn.h"
#include "ShineLineOut.h"
#include "MathUtils.h"

using namespace std;

ShineLineMgr::ShineLineMgr() {
	_counter = 0;
}

void ShineLineMgr::regist() {
	float x = SHINE_X + randf2(400);
	float y = SHINE_Y + randf2(400);
	_list.push_back(make_shared<ShineLineIn>(x,y));
}

bool ShineLineMgr::update() {
	_counter++;
	// １フレーム目の描画時に十分パーティクルが存在するように最初だけ沢山更新する
	if (_counter == 1) {
		for (int i = 0; i < 100; i++) {
			update();
		}
	}
	for(int i=0; i<10; i++){
		regist();
	}
	auto it = _list.begin();
	while (it != _list.end()) {
		if ((*it)->update() == false) {
			it = _list.erase(it);
		}
		else {
			++it;
		}
	}
	return true;
}

void ShineLineMgr::draw() {
	for (auto a : _list) {
		a->draw();
	}
}

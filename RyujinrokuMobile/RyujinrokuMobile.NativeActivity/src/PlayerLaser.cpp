#include "PlayerLaser.h"
#include "Utils.h"

const static int N = 8;

PlayerLaser::PlayerLaser() {
	_counter = 0;
	_r = 0;
	_a = 0;
	for (int i = 0; i < N; i++) {
		std::vector<PlayerLaserFactor*> line;
		for (int j = 0; j < 1000; j += 10) {
			line.push_back(new PlayerLaserFactor(-j));
		}
		_list.push_back(line);
	}
}

PlayerLaser::~PlayerLaser() {
	for (auto l : _list) {
		for (auto f : l) {
			delete f;
		}
	}
}

void PlayerLaser::update() {
	for (auto l : _list) {
		_a = 1.5+stdRandf2(0.2);	//点滅させる
		for (auto f : l) {
			f->update();
		}
	}
	if (_counter<=120) {
		_r = Utils::getSinValue_90(_counter / 120.f, 300);
	}
	_counter++;
}

void PlayerLaser::draw(float x, float y) {
	int i = 0;
	for (auto l : _list) {
		int cnt = _counter+480/N*i;
		for (auto f : l) {
			f->draw(x + cos(PI2 / 480 * cnt) * _r, y);
		}
		for (int i = 0; i < 1; i++) {
			DrawRotaGraph(x + cos(PI2 / 480 * cnt) * _r, y, _a, 0, Image::getIns()->playerLaserRoot, TRUE);
		}
		i++;
	}
}

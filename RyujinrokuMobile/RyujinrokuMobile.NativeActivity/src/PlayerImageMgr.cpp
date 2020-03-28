#include "PlayerImageMgr.h"
#include <DxLib.h>
#include "Pad.h"

constexpr static int ITVL = 5;

PlayerImageMgr::PlayerImageMgr(Player* player)
{
	_imgRight[0] = LoadGraph("dat/image/player/body/migi0.5.png");
	_imgRight[1] = LoadGraph("dat/image/player/body/migi1.0.png");
	_imgRight[2] = LoadGraph("dat/image/player/body/migi1.5.png");
	_imgRight[3] = LoadGraph("dat/image/player/body/migi2-1.png");
	_imgRight[4] = LoadGraph("dat/image/player/body/migi2-2.png");
	_imgRight[5] = LoadGraph("dat/image/player/body/migi2-3.png");
	_imgLeft[0] = LoadGraph("dat/image/player/body/hidari0.5.png");
	_imgLeft[1] = LoadGraph("dat/image/player/body/hidari1.0.png");
	_imgLeft[2] = LoadGraph("dat/image/player/body/hidari1.5.png");
	_imgLeft[3] = LoadGraph("dat/image/player/body/hidari2-1.png");
	_imgLeft[4] = LoadGraph("dat/image/player/body/hidari2-2.png");
	_imgLeft[5] = LoadGraph("dat/image/player/body/hidari2-3.png");
	_imgUp[0] = LoadGraph("dat/image/player/body/ue1.png");
	_imgUp[1] = LoadGraph("dat/image/player/body/ue2-1.png");
	_imgUp[2] = LoadGraph("dat/image/player/body/ue2-2.png");
	_imgUp[3] = LoadGraph("dat/image/player/body/ue2-3.png");
	_imgDown[0] = LoadGraph("dat/image/player/body/shita1.png");
	_imgDown[1] = LoadGraph("dat/image/player/body/shita2-1.png");
	_imgDown[2] = LoadGraph("dat/image/player/body/shita2-2.png");
	_imgDown[3] = LoadGraph("dat/image/player/body/shita2-3.png");
	_imgStand[0] = LoadGraph("dat/image/player/body/seishi0.png");
	_imgStand[1] = LoadGraph("dat/image/player/body/seishi1.png");
	_imgStand[2] = LoadGraph("dat/image/player/body/seishi2.png");
	_imgStand[3] = -1;

	_imgRightD[0] = LoadGraph("dat/image/player/bodyDress/migi0.5.png");
	_imgRightD[1] = LoadGraph("dat/image/player/bodyDress/migi1.0.png");
	_imgRightD[2] = LoadGraph("dat/image/player/bodyDress/migi1.5.png");
	_imgRightD[3] = LoadGraph("dat/image/player/bodyDress/migi2-1.png");
	_imgRightD[4] = LoadGraph("dat/image/player/bodyDress/migi2-2.png");
	_imgRightD[5] = LoadGraph("dat/image/player/bodyDress/migi2-3.png");
	_imgLeftD[0] = LoadGraph("dat/image/player/bodyDress/hidari0.5.png");
	_imgLeftD[1] = LoadGraph("dat/image/player/bodyDress/hidari1.0.png");
	_imgLeftD[2] = LoadGraph("dat/image/player/bodyDress/hidari1.5.png");
	_imgLeftD[3] = LoadGraph("dat/image/player/bodyDress/hidari2-1.png");
	_imgLeftD[4] = LoadGraph("dat/image/player/bodyDress/hidari2-2.png");
	_imgLeftD[5] = LoadGraph("dat/image/player/bodyDress/hidari2-3.png");
	_imgUpD[0] = LoadGraph("dat/image/player/bodyDress/ue1.png");
	_imgUpD[1] = LoadGraph("dat/image/player/bodyDress/ue2-1.png");
	_imgUpD[2] = LoadGraph("dat/image/player/bodyDress/ue2-2.png");
	_imgUpD[3] = LoadGraph("dat/image/player/bodyDress/ue2-3.png");
	_imgDownD[0] = LoadGraph("dat/image/player/bodyDress/shita1.png");
	_imgDownD[1] = LoadGraph("dat/image/player/bodyDress/shita2-1.png");
	_imgDownD[2] = LoadGraph("dat/image/player/bodyDress/shita2-2.png");
	_imgDownD[3] = LoadGraph("dat/image/player/bodyDress/shita2-3.png");
	_imgStandD[0] = LoadGraph("dat/image/player/bodyDress/seishi0.png");
	_imgStandD[1] = LoadGraph("dat/image/player/bodyDress/seishi1.png");
	_imgStandD[2] = LoadGraph("dat/image/player/bodyDress/seishi2.png");
	_imgStandD[3] = -1;

	_rightCount = -999;
	_leftCount = -999;
	_downCount = -999;
	_upCount = -999;
	_count = 0;

	_player = player;
}

PlayerImageMgr::~PlayerImageMgr()
{
	for (int i = 0; i < 6; i++) {
		DeleteGraph(_imgRight[i]);
		DeleteGraph(_imgLeft[i]);
	}
	for (int i = 0; i < 4; i++) {
		DeleteGraph(_imgDown[i]);
		DeleteGraph(_imgUp[i]);
		DeleteGraph(_imgStand[i]);
	}
}

void PlayerImageMgr::update()
{
	if (Pad::getIns()->get(ePad::left) > 0) {
		_leftCount = _leftCount<0 ? 0 : _leftCount + 1;
	}
	else if (Pad::getIns()->get(ePad::up) > 0) {
		_leftCount = _leftCount>0 ? 0 : _leftCount-1;
		_upCount   = _upCount  <0 ? 0 : _upCount  +1;
	}
	else if (Pad::getIns()->get(ePad::right) > 0) {
		_leftCount  = _leftCount >0 ? 0 : _leftCount  - 1;
		_upCount    = _upCount   >0 ? 0 : _upCount    - 1;
		_rightCount = _rightCount<0 ? 0 : _rightCount + 1;
	}
	else if (Pad::getIns()->get(ePad::down) > 0) {
		_leftCount  = _leftCount >0 ? 0 : _leftCount  - 1;
		_upCount    = _upCount   >0 ? 0 : _upCount    - 1;
		_rightCount = _rightCount>0 ? 0 : _rightCount - 1;
		_downCount  = _downCount <0 ? 0 : _downCount  + 1;
	}
	else {
		_leftCount  = _leftCount >0 ? 0 : _leftCount  - 1;
		_upCount    = _upCount   >0 ? 0 : _upCount    - 1;
		_rightCount = _rightCount>0 ? 0 : _rightCount - 1;
		_downCount  = _downCount >0 ? 0 : _downCount  - 1;
		_count++;
	}
}

int PlayerImageMgr::getImage()
{
	if (_player->isLaser()) {
		if (_leftCount > 0) {
			return _imgLeftD[_leftCount < ITVL * 3 ? _leftCount / ITVL : ((_leftCount / ITVL) % 3) + 3];
		}
		else if (_upCount > 0) {
			return _imgUpD[_upCount < ITVL ? 0 : ((_upCount / ITVL) % 3) + 1];
		}
		else if (_rightCount > 0) {
			return _imgRightD[_rightCount < ITVL * 3 ? _rightCount / ITVL : ((_rightCount / ITVL) % 3) + 3];
		}
		else if (_downCount > 0) {
			return _imgDownD[_downCount < ITVL ? 0 : ((_downCount / ITVL) % 3) + 1];
		}
		else {
			if (0 > _leftCount && _leftCount >= -ITVL * 3) {
				return _imgLeftD[2 - ((-_leftCount) - 1) / ITVL];
			}
			else if (0 > _upCount && _upCount >= -ITVL - 1) {
				return _imgUpD[0];
			}
			else if (0 > _rightCount && _rightCount > -ITVL * 3) {
				return _imgRightD[2 - ((-_rightCount) - 1) / ITVL];
			}
			else if (0 > _downCount && _downCount >= -ITVL - 1) {
				return _imgDownD[0];
			}
			else {
				return _imgStandD[(_count / ITVL) % 3];
			}
		}
	}
	else {
		if (_leftCount > 0) {
			return _imgLeft[_leftCount < ITVL * 3 ? _leftCount / ITVL : ((_leftCount / ITVL) % 3) + 3];
		}
		else if (_upCount > 0) {
			return _imgUp[_upCount < ITVL ? 0 : ((_upCount / ITVL) % 3) + 1];
		}
		else if (_rightCount > 0) {
			return _imgRight[_rightCount < ITVL * 3 ? _rightCount / ITVL : ((_rightCount / ITVL) % 3) + 3];
		}
		else if (_downCount > 0) {
			return _imgDown[_downCount < ITVL ? 0 : ((_downCount / ITVL) % 3) + 1];
		}
		else {
			if (0 > _leftCount && _leftCount >= -ITVL * 3) {
				return _imgLeft[2 - ((-_leftCount) - 1) / ITVL];
			}
			else if (0 > _upCount && _upCount >= -ITVL - 1) {
				return _imgUp[0];
			}
			else if (0 > _rightCount && _rightCount > -ITVL * 3) {
				return _imgRight[2 - ((-_rightCount) - 1) / ITVL];
			}
			else if (0 > _downCount && _downCount >= -ITVL - 1) {
				return _imgDown[0];
			}
			else {
				return _imgStand[(_count / ITVL) % 3];
			}
		}
	}
}

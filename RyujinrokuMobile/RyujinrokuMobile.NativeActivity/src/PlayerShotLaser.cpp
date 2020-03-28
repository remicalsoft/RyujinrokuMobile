#include "PlayerShotLaser.h"
#include <DxLib.h>

using namespace std;

PlayerShotLaser::PlayerShotLaser(Player *player)
{
	_player = player;
}


PlayerShotLaser::~PlayerShotLaser()
{
	_list.clear();
}

bool PlayerShotLaser::update()
{
	_list.clear();
	float shift = Pad::getIns()->get(ePad::slow);
	if (shift > 20) {
		shift = 20;
	}
	float x;
	float y;
	{
		x = _player->getX() - 38 + shift;
		y = _player->getY();
		while (y > _player->getY()-150) {
			y -= 24 + GetRand(24);
			_list.push_back(make_shared<Factor>(x, y, 24 + GetRand(24)));
		}
		while (y > -90) {
			y -= 10 + GetRand(10);
			_list.push_back(make_shared<Factor>(x, y, 32 + GetRand(32)));
		}
	}
	{
		x = _player->getX() + 38 - shift;
		y = _player->getY();
		while (y > _player->getY()-150) {
			y -= 24 + GetRand(24);
			_list.push_back(make_shared<Factor>(x, y, 24 + GetRand(24)));
		}
		while (y > -90) {
			y -= 10 + GetRand(10);
			_list.push_back(make_shared<Factor>(x, y, 32 + GetRand(32)));
		}
	}
	return false;
}

void PlayerShotLaser::draw()
{
	for(shared_ptr<Factor> f : _list){
		SetDrawBlendMode(DX_BLENDMODE_ADD, f->a);
		DrawRotaGraph(f->x, f->y, 1.0, 0.0, Image::getIns()->playerShotLaser[f->type], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

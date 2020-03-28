#include "Player.h"
#include <DxLib.h>
#include "Define.h"
#include "Image.h"
#include "Pad.h"
#include "PlayerShotStraight.h"
#include "PlayerShotTail.h"
#include "GameData.h"
#include "SE.h"
#include "Replayer.h"
#include "DebugMode.h"
#include "SavedData.h"
#include "StoreBuyScene.h"

const static float SPEED = 9;

const static int SHOT_ITVL_FRAME = 4;
const static int BALL_POS = 40;
const static float HIT_RANGE = 4.35f;	//実測5.5
const static float GRAZE_RANGE = 35.0f;

using namespace std;

void Player::startInvincible(int endtime)
{
	_isInvincible = true;
	_counterInvincible = 0;
	_EndTimeInvincible = endtime;
}

void Player::doBomb()
{
	startInvincible(400);
	Replayer::getIns()->bomb();
	_bomb = new Bomb(this);
	_implShake->onShake(eShakeType::eShakeType_BOMB);
}

Player::Player(IOnPlayerDiedListener *impl, IShakeListener *implShake, bool isFromPractice, bool isFromSpellPractice) :
 _x(OUT_W/2)
,_y(OUT_H*4/5)
{
	_isFromPractice = isFromPractice;
	_isFromSpellPractice = isFromSpellPractice;
	_implPlayerDied = impl;
	_implShake = implShake;
	_imgHitMark = LoadGraph("dat/image/player/hitMark.png");
	_counter = 0;
	_isInvincible = false;
	_counterInvincible = 0;
	_EndTimeInvincible = 0;
	_bomb = nullptr;
	_optionPosX=0;
	_optionPosY=0;
	_dressCounter = 100;
	_imgMgr = new PlayerImageMgr(this);
	_showPressingCount = 0;
	_isLaser = false;
	_playerShotLaser = new PlayerShotLaser(this);
	_isLaserNowShooting = false;
}

Player::~Player()
{
	DeleteGraph(_imgHitMark);
	delete _imgMgr;
}

bool Player::update() {

	this->move();
	_imgMgr->update();
	if (Pad::getIns()->get(ePad::shot)%SHOT_ITVL_FRAME==1) {
		if (!_isLaser) {
			if (!_implTalkStatusGettable->isNowTalking()) {
				registerShot();
			}
		}
	}
	for (list<shared_ptr<PlayerShot>>::iterator it = _shotList.begin(); it != _shotList.end();) {
		if ((*it)->update() == false) {
			it = _shotList.erase(it);
		}
		else {
			it++;
		}
	}
	for (list<shared_ptr<GrazeEffect>>::iterator it = _grazeList.begin(); it != _grazeList.end();) {
		if ((*it)->update() == false) {
			it = _grazeList.erase(it);
		}
		else {
			it++;
		}
	}
	if (_isInvincible) {
		_counterInvincible++;
		if (_counterInvincible== _EndTimeInvincible) {
			_isInvincible = false;
		}
	}
	if (_bomb==nullptr && Pad::getIns()->get(ePad::bom)==1) {
		if (!_implTalkStatusGettable->isNowTalking()) {
			if (GameData::getIns()->bomb >= BOMB_PARTS_N || 
				SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb] || 
				SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2]) {

				if (GameData::getIns()->bomb >= BOMB_PARTS_N) {
					GameData::getIns()->bomb -= BOMB_PARTS_N;
				}
				else if (SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2]) {
					SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb2] = false;
					SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb2] = false;
					GameData::getIns()->usedBombItemNum++;
				}
				else if(SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb]){
					SavedData::getIns()->dat.isEquiped[eEquipItem_Bomb] = false;
					SavedData::getIns()->dat.hasEquipableItem[eEquipItem_Bomb] = false;
					GameData::getIns()->usedBombItemNum++;
				}
				else {
					//nothing
				}
				doBomb();
			}
		}
	}
	if (_bomb != nullptr) {
		_boss->disableSpellcardGettable();
		if (_bomb->update() == false) {
			delete _bomb;
			_bomb = nullptr;
		}
	}

	if (SavedData::getIns()->dat.isEquiped[eEquipItem_Dress]) {
		if (!_implTalkStatusGettable->isNowTalking()) {
			if (Pad::getIns()->get(ePad::change) == 1) {
				_isLaser = !_isLaser;
				SE::getIns()->setPlay(eSE::eSE_dress);
				_dressCounter = 0;
			}
		}
	}
	_dressCounter++;

	if (_isLaser) {
		_playerShotLaser->update();
		if (Pad::getIns()->get(ePad::shot) > 0) {
			_isLaserNowShooting = true;
		}
		else {
			_isLaserNowShooting = false;
		}
	}
	else {
		_isLaserNowShooting = false;
	}

	//低速中の魔方陣描画のためのカウント
	if (Pad::getIns()->get(ePad::slow) > 0)
	{
		_showPressingCount++;
		if (_showPressingCount > 32)
			_showPressingCount = 32;
	}
	else
	{
		_showPressingCount--;
		if (_showPressingCount < 0)
			_showPressingCount = 0;
	}

	float mul = Pad::getIns()->get(ePad::slow) > 0 ? 0.7 : 1;
	_optionPosX= -BALL_POS*mul;
	_optionPosY=  BALL_POS*mul + sin(PI * 2 / 60 * _counter) * 10 * mul;
	_counter++;
	return true;
}

void Player::draw() {

	if (_isLaserNowShooting) {
		_playerShotLaser->draw();
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _showPressingCount * 4);
	DrawRotaGraphF(_x, _y, 1.0, +PI2 / 240 * _counter, Image::getIns()->playerRing, TRUE);
	DrawRotaGraphF(_x, _y, 1.0, -PI2 / 240 * _counter, Image::getIns()->playerRing, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (auto p : _grazeList) {
		p->draw();
	}
	for (auto p : _shotList) {
		p->draw();
	}
	if (!_isInvincible || _isInvincible && _counter % 2) {
		DrawRotaGraphF(_x +_optionPosX, _y +_optionPosY, 1.0, 0, Image::getIns()->playerBall, TRUE);
		DrawRotaGraphF(_x -_optionPosX, _y +_optionPosY, 1.0, 0, Image::getIns()->playerBall, TRUE);
		int img = _imgMgr->getImage();
		if (_dressCounter < 10) {
			int w = 0, h = 0;
			GetGraphSize(img, &w, &h);
			int x1 = _x - w / 2 * _dressCounter / 10;
			int x2 = _x + w / 2 * _dressCounter / 10;
			int x3 = _x + w / 2 * _dressCounter / 10;
			int x4 = _x - w / 2 * _dressCounter / 10;
			int y1 = _y - h / 2;
			int y2 = _y - h / 2;
			int y3 = _y + h / 2;
			int y4 = _y + h / 2;
			DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, img, TRUE);
		}
		else {
			DrawRotaGraphF(_x, _y, 1.0, 0, img, TRUE);
		}
	}
}

void Player::reset()
{
	_x = OUT_W / 2;
	_y = OUT_H * 4 / 5;
}

void Player::setTalkStatusGettable(ITalkStatusGettable * implTalkStatusGettable)
{
	_implTalkStatusGettable = implTalkStatusGettable;
}

void Player::drawHitMark()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (_showPressingCount/2)*16);
	DrawRotaGraph(_x, _y, 1.0, PI * 2 / 180 * _counter, _imgHitMark, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (_bomb != nullptr) {
		_bomb->draw();
	}
}

std::list<std::shared_ptr<PlayerShot>>* Player::getShotList()
{
	return &_shotList;
}

float Player::getHitRange()
{
	double r = HIT_RANGE;
	if (SavedData::getIns()->dat.isEquiped[eEquipItem::eEquipItem_Jacket]) {
		r *= 0.9;
	}
	if (SavedData::getIns()->dat.isEquiped[eEquipItem::eEquipItem_Jacket2]) {
		r *= 0.9;
	}
	return r;
}

float Player::getGrazeRange()
{
	return GRAZE_RANGE;
}

void Player::move() {
	float move_x = 0, move_y = 0;
	if (Pad::getIns()->get(ePad::left) > 0) {
		move_x -= SPEED;
	}
	if (Pad::getIns()->get(ePad::right) > 0) {
		move_x += SPEED;
	}
	if (Pad::getIns()->get(ePad::down) > 0) {
		move_y += SPEED;
	}
	if (Pad::getIns()->get(ePad::up) > 0) {
		move_y -= SPEED;
	}
	if (move_x && move_y) { //斜め移動
		move_x /= sqrt(2.0);
		move_y /= sqrt(2.0);
	}
	if (Pad::getIns()->get(ePad::slow) > 0) {
		move_x /= 3;
		move_y /= 3;
	}
	if (move_x + _x < IN_X) {
		_x = IN_X;
	}
	else if (move_x + _x > IN_X + IN_W) {
		_x = IN_X + IN_W;
	}
	else {
		_x += move_x;
	}
	if (move_y + _y < IN_Y) {
		_y = IN_Y;
	}
	else if (move_y + _y > IN_Y + IN_H) {
		_y = IN_Y + IN_H;
	}
	else {
		_y += move_y;
	}
}

void Player::registerShot(){
	double div = Pad::getIns()->get(ePad::slow) > 0 ? 3 : 1;
	float mul = Pad::getIns()->get(ePad::slow) > 0 ? 0.7 : 1;
	int power = GameData::getIns()->power;
	if(power>500){
		power = 500;
	}
	float powerStraight[6] = { (124 - 16) / 2 ,(124 - 12) / 4 ,(124 - 8) / 4 ,(124 - 4) / 4 ,(124 - 0) / 4, (124 + 4) / 4, };
	float powerTail[6]     = { ( 62 - 20) / 2 ,( 62 - 15) / 2 ,( 62 -10) / 2 ,( 62 - 5) / 2 ,( 62 - 0) / 2, ( 62 + 2) / 2, };
	for (int i = 0; i < 6; i++) {
		if (SavedData::getIns()->dat.isEquiped[eEquipItem_Soul]) {
			powerStraight[i] *= 1.03;
			powerTail[i] *= 1.02;
		}
		if (SavedData::getIns()->dat.isEquiped[eEquipItem_Soul2]) {
			powerStraight[i] *= 1.03;
			powerTail[i] *= 1.02;
		}
	}
	_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotStraight(_x - 25/div, _y - 25, powerStraight[power/100])));
	_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotStraight(_x + 25/div, _y - 25, powerStraight[power/100])));
	_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotTail(_x - BALL_POS*mul, _y + BALL_POS*mul, powerTail[power/100])));
	_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotTail(_x + BALL_POS*mul, _y + BALL_POS*mul, powerTail[power/100])));
	if (power >= 100) {
		_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotStraight(_x - 70 / div, _y - 5, powerStraight[power / 100])));
		_shotList.push_back(shared_ptr<PlayerShot>(new PlayerShotStraight(_x + 70 / div, _y - 5, powerStraight[power / 100])));
	}
	SE::getIns()->setPlay(eSE::eSE_playerShot);
}

void Player::die() {
	Replayer::getIns()->die();
	//	startInvincible();
	SE::getIns()->setPlay(eSE_playerDead);
	_boss->disableSpellcardGettable();

	if (DebugMode::getIns()->isPlayerInvincible == true) {
		return;	//被弾を無効化
	}

	if (_isFromPractice || _isFromSpellPractice) {
		startInvincible(180);
	}
	else {
		_implPlayerDied->onPlayerDied();
	}
}


bool Player::isBombing() {
	return _bomb == nullptr ? false : true;
}

float Player::getBombR()
{
	if (_bomb != nullptr) {
		return _bomb->getBombR();
	}
	return 0.0f;
}

void Player::finishBomb()
{
	if (_bomb != nullptr) {
		_bomb->finish();
	}
}

void Player::registerGraze()
{
	_grazeList.push_back(shared_ptr<GrazeEffect>(new GrazeEffect(_x,_y)));
	SE::getIns()->setPlay(eSE::eSE_graze);
}

float Player::getLaserDamageValue()
{
	int power = GameData::getIns()->power;
	float value = 19.38 + 5.13 * power / 500;
	return value*1.17;
}

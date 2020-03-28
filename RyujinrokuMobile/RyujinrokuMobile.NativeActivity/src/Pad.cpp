#include "Pad.h"
#include <DxLib.h>
#include "Keyboard.h"
#include "Define.h"
#include "Utils.h"
#include <string>

using namespace std;

const static char* PATH = "SavedData/Keyconfig.dat";

Pad::Pad() {
	string path = Utils::getSavePath();
	path += PATH;
	FILE *fp = fopen(path.c_str(), "rb");
	if (fp == NULL) {
		initialize();
	}
	else {
		fread(_padID.padArray, sizeof(int)*PAD_TYPE_NUM, 1, fp);
		fclose(fp);
	}
	/*
	_padID.down = 0;
	_padID.left = 1;
	_padID.right = 2;
	_padID.up = 3;
	_padID.bom = 4;
	_padID.shot = 5;
	_padID.slow = 11;
	_padID.start = 13;
	_padID.change = 6;
	*/
	_isReplaying = false;
}

Pad::~Pad() {
}

void Pad::initialize()
{
	_padID.padArray[ePad::down] = 0;
	_padID.padArray[ePad::left] = 1;
	_padID.padArray[ePad::right] = 2;
	_padID.padArray[ePad::up] = 3;
	_padID.padArray[ePad::bom] = 4;
	_padID.padArray[ePad::shot] = 5;
	_padID.padArray[ePad::slow] = 11;
	_padID.padArray[ePad::start] = 12;
	_padID.padArray[ePad::change] = 8;
}

void Pad::save()
{
	string path = Utils::getSavePath();
	path += PATH;
	FILE *fp = fopen(path.c_str(), "wb");
	if (fp == NULL) {
		ERR("Keyconfigが書き込めませんでした");
	}
	fwrite(_padID.padArray, sizeof(int)*PAD_TYPE_NUM, 1, fp);
	fclose(fp);
}

//引数１と引数２のうち大きい方を引数１に代入する
void marge(int *p, int k) {
	*p = *p>k ? *p : k;
}

//パッドとキーボードの両方の入力をチェックする関数
void Pad::update() {
	if (_isReplaying) {
		return;
	}
	int i, PadInput, mul = 1;
	PadInput = GetJoypadInputState(DX_INPUT_PAD1);//パッドの入力状態を取得
	for (i = 0; i<16; i++) {
		if (PadInput & mul) {
			pad[i]++;
		}
		else {
			pad[i] = 0;
		}
		mul *= 2;
	}
	marge(&pad[_padID.padArray[ePad::left]], Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT));
	marge(&pad[_padID.padArray[ePad::up]], Keyboard::getIns()->getPressingCount(KEY_INPUT_UP));
	marge(&pad[_padID.padArray[ePad::right]], Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT));
	marge(&pad[_padID.padArray[ePad::down]], Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN));
	marge(&pad[_padID.padArray[ePad::shot]], Keyboard::getIns()->getPressingCount(KEY_INPUT_Z));
	marge(&pad[_padID.padArray[ePad::shot]], Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN));
	marge(&pad[_padID.padArray[ePad::bom]], Keyboard::getIns()->getPressingCount(KEY_INPUT_X));
	marge(&pad[_padID.padArray[ePad::slow]], Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT));
	marge(&pad[_padID.padArray[ePad::start]], Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE));
	marge(&pad[_padID.padArray[ePad::change]], Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL));
	marge(&pad[_padID.padArray[ePad::change]], Keyboard::getIns()->getPressingCount(KEY_INPUT_C));
}

//渡されたパッドキー番号の入力状態を返す。返り値が-1なら不正
int Pad::get(ePad eID) {
	return pad[_padID.padArray[eID]];
	/*
	switch (eID) {
	case left:
		return pad[_padID.left];
	case up:
		return pad[_padID.up];
	case right:
		return pad[_padID.right];
	case down:
		return pad[_padID.down];
	case shot:
		return pad[_padID.shot];
	case bom:
		return pad[_padID.bom];
	case slow:
		return pad[_padID.slow];
	case start:
		return pad[_padID.start];
	case change:
		return pad[_padID.change];
	}
	return 0;
	*/
}

void Pad::setPadData(PadID pad)
{
	memcpy(_padID.padArray, pad.padArray, sizeof(int)*PAD_TYPE_NUM);
}

void Pad::startReplay(int padArray)
{
}

void Pad::setPadStatus(int replayPad[PAD_KEY_NUM])
{
	memcpy(pad, replayPad, sizeof(pad));
}

/*
void Pad::inputPadData(int *indata) {
	*indata = _padID.shot;
	*(indata + 1) = _padID.bom;
	*(indata + 2) = _padID.slow;
	*(indata + 3) = _padID.change;
	*(indata + 4) = _padID.start;
}

void Pad::registPadData(int *indata) {
	_padID.shot = *indata;
	_padID.bom = *(indata + 1);
	_padID.slow = *(indata + 2);
	_padID.change = *(indata + 3);
	_padID.start = *(indata + 4);
}
*/
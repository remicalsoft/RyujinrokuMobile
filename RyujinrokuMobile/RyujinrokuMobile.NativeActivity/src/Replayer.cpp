#include "Replayer.h"
#include <memory>
#include <Windows.h>
#include "Utils.h"
#include "Error.h"
#include "Define.h"
#include "Toast.h"
#include "GameCounter.h"
#include "Keyboard.h"

using namespace std;

const static int MAX_SPEED = 256;

vector<int> SPEED = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	20,
	50,
	100
};

Replayer::Replayer()
{
	_recodeFps = 0;
	_fps = 0;
	_frameID = 0;
	_fp = nullptr;
	_preChangedFrame = 0;
	_startTime = 0;
	_status = eReplayStatus_Default;
	memset(_replayPad, 0, sizeof(_replayPad));
	_index = 0;
	_preChangedFrame = 0;
	_playSpeedID = 0;
	_counter = 0;
	_font = CreateFontToHandle(FONT, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	_status = eReplayStatus_Default;
}


Replayer::~Replayer()
{
	DeleteFontToHandle(_font);
}

void Replayer::startRecode(int randSeed, eReplayType type)
{
	clear();
	_header.init();
	_startTime = GetNowCount();
	_header.randSeed = randSeed;
	_header.replayType = type;
	memcpy(_header.gameVersion, VERSION, sizeof(_header.gameVersion));

	const int *padID = Pad::getIns()->getPadID();
	memcpy(_padID.padArray, padID, sizeof(int)*PAD_TYPE_NUM);
	const int *prePad = Pad::getIns()->getPad();
	memcpy(_prePad,         prePad, sizeof(int)*PAD_KEY_NUM);
	memcpy(_firstPadStatus, prePad, sizeof(int)*PAD_KEY_NUM);
	_status = eReplayStatus_Recoding;
}

void Replayer::endRecode(bool recode)
{
	if (recode && _status == eReplayStatus_Recoding) {
		/*
		string pathR = Utils::getSavePath();
		pathR += "リプレイデータ";
		if (!Utils::existsFolder(pathR.c_str())) {
			CreateDirectory(pathR.c_str(), NULL);
		}
		_header.playTime = GetNowCount() - _startTime;
		strcpy(_header.name, "--------");
		char fileName[256];
		int n = Utils::creatableNumOfReplayFileName();
		sprintf(fileName, "リプレイデータ/%03d.rpy", n);
		string path = Utils::getSavePath();
		path += fileName;
		_fp = fopen(path.c_str(), "wb");
		if (_fp == NULL) {
			ERR("リプレイデータフォルダ内のファイルにアクセスが出来ません");
		}
		fwrite(&_header, sizeof(ReplayHeader), 1, _fp);
		int fpsTotalNum = _fpsList.size();
		fwrite(&fpsTotalNum, sizeof(int), 1, _fp);
		for (short int f : _fpsList) {
			fwrite(&f, sizeof(short int), 1, _fp);
		}
		fwrite(_firstPadStatus, sizeof(int)*PAD_KEY_NUM,  1, _fp);
		fwrite(_padID.padArray, sizeof(int)*PAD_TYPE_NUM, 1, _fp);
		for (DataSet *d : _list) {
			fwrite(d, sizeof(*d), 1, _fp);
		}
		fclose(_fp);
		_fp = nullptr;
		Toast::getIns()->add("リプレイデータを保存しました");
		*/
	}
	_status = eReplayStatus_Default;
	clear();
}

void Replayer::clear()
{
	_fps = 0;
	_frameID = 0;
	_playSpeedID = 0;
	_preChangedFrame = 0;
	_counter = 0;
	_recodeFps = 0;
	_fpsList.clear();
	for (DataSet *d : _list) {
		delete d;
	}
	_list.clear();
}

void Replayer::recode()
{
	if (_counter % 180 == 0) {
		_fpsList.push_back((short int)(_fps*10));
	}
	_counter++;
	_frameID++;
	const int* nowPad = Pad::getIns()->getPad();
	for (char i = 0; i < PAD_KEY_NUM; i++) {
		if (_prePad[i] > 0 && nowPad[i] == 0 || _prePad[i] == 0 && nowPad[i] > 0) {
			if (_frameID - _preChangedFrame >= (1<<16)) {
				printfDx("18分操作していなかったのでリプレイデータがバグります\n");
				printfDx("このメッセージはDeleteキーを押すと消えます\n");
			}
			unsigned short subFrame = _frameID - _preChangedFrame;
			_list.push_back(new DataSet(subFrame, i));
			_preChangedFrame = _frameID;
//			printfDx("%d %d\n", subFrame,i);
		}
		_prePad[i] = nowPad[i];
	}
}

void Replayer::startReplay(const char *fileName)
{
	clear();
	_index = 0;
	_preChangedFrame = 0;
	_playSpeedID = 0;
	string path = Utils::getSavePath();
	path += fileName;
	_fp = fopen(path.c_str(), "rb");
	if (_fp == NULL) {
		ERR("リプレイデータフォルダ内のファイルにアクセスが出来ません");
	}
	fread(&_header, sizeof(ReplayHeader), 1, _fp);
	int fpsTotalNum = 0;
	fread(&fpsTotalNum, sizeof(int), 1, _fp);
	int fps = 0;
	for (int i = 0; i < fpsTotalNum; i++) {
		fread(&fps, sizeof(short int), 1, _fp);
		_fpsList.push_back(fps);
	}
	fread(_firstPadStatus, sizeof(int)*PAD_KEY_NUM, 1, _fp);
	fread(_padID.padArray, sizeof(int)*PAD_TYPE_NUM, 1, _fp);
	while (true) {
		DataSet *d = new DataSet();
		int ret = fread(d, sizeof(*d), 1, _fp);
		if (ret <= 0) {
			delete d;
			break;
		}
		else {
			_list.push_back(d);
		}
	}
	fclose(_fp);
	_fp = nullptr;

	memcpy(_replayPad, _firstPadStatus, sizeof(_replayPad));
	Pad::getIns()->setPadStatus(_replayPad);
	Pad::getIns()->setPadData(_padID);
	_status = eReplayStatus_Replaying;
}

void Replayer::endReplay()
{
	clear();
	_status = eReplayStatus_Default;
}

void Replayer::update()
{
	if (_status == eReplayStatus_Replaying) {
		if (_counter % 180 == 0) {
			int n = _counter / 180;
			if (n<_fpsList.size()) {
				_recodeFps = _fpsList[n] / 10.f;
			}
		}
		_counter++;
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {
			if (_playSpeedID < SPEED.size() - 1) {
				_playSpeedID++;
			}
		}
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {
			if (_playSpeedID > 0) {
				_playSpeedID--;
			}
		}
	}
}

bool Replayer::updatePadStatus()
{
	_frameID++;

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
		return false;
	}

	for (int i = 0; i < PAD_KEY_NUM; i++) {
		if (_replayPad[i] > 0) {
			_replayPad[i]++;
		}
	}
	while (_index < _list.size()) {
		if ((int)(_list.at(_index)->frameID) + _preChangedFrame == _frameID) {
			if (_replayPad[_list.at(_index)->padID] == 0) {
				_replayPad[_list.at(_index)->padID] = 1;
			}
			else {
				_replayPad[_list.at(_index)->padID] = 0;
			}
			_preChangedFrame += _list.at(_index)->frameID;
			_index++;
//			printfDx("%d %d\n", _list.at(_index)->frameID, _list.at(_index)->padID);
		}
		else {
			break;
		}
	}
	Pad::getIns()->setPadStatus(_replayPad);
	return true;
}

void Replayer::draw()
{
	DrawFormatStringToHandle(1184, 20, GetColor(255, 255, 255), _font, "%.1ffps", _recodeFps);
	DrawFormatStringToHandle(960, WIN_H -110, GetColor(255, 255, 255), _font, "%d倍速", SPEED[_playSpeedID]);
	DrawFormatStringToHandle(960, WIN_H - 90, GetColor(200, 200, 200), _font, "キーボード上下キーで速度変更");
}

int Replayer::getPlaySpeed()
{
	return SPEED.at(_playSpeedID);
}

void Replayer::setSrand()
{
	SRand(_header.randSeed);
	srand(_header.randSeed);
}

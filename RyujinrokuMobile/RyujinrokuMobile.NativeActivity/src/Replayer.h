#pragma once

#include "Singleton.h"
#include <vector>
#include "Pad.h"
#include "Define.h"

/*
 * @brief リプレイデータ管理
 リプレイデータはゲーム最初のパッドの入力状態と乱数のシードを覚えて置き
 更に入力状態が変わったframeIDと変わったパッドのIDを保存して起き、
 それを元にパッドの入力状態を再現する。
 必要なデータはint型のframeIDとどのパッドIDが変わったかを示すpadIDの計5バイトだけである
*/

enum eReplayType {
	eReplayType_Normal,
	eReplayType_Practice,
	eReplayType_SpellPractice,
};

enum eReplayStatus {
	eReplayStatus_Default,
	eReplayStatus_Recoding,
	eReplayStatus_Replaying,
	eReplayStatus_Disabled,
};

class ReplayHeader {
public:
	const static int NAME_MAX_LEN = 64;
	unsigned char dataVersion;
	unsigned char gameVersion[10];
	char name[NAME_MAX_LEN+1];
	unsigned char stage;
	char          isSpellPractice;
	unsigned char level;
	unsigned long long equipItem;
	int randSeed;
	unsigned short hitCount;
	unsigned short bombCount;
	unsigned int   score;
	unsigned char  clearStageN;
	unsigned int   playTime;
	eReplayType replayType;
	ReplayHeader() {
		init();
	}
	void init() {
		dataVersion = 0;
		memset(gameVersion, 0, sizeof(char) * 10);
		memset(name, 0, sizeof(name));
		stage = 0;
		isSpellPractice = false;
		level = 0;
		equipItem = 0;
		randSeed = 0;
		hitCount = 0;
		bombCount = 0;
		score = 0;
		clearStageN = 0;
		playTime = 0;
		replayType = eReplayType_Normal;
	}
};

class Replayer : public Singleton<Replayer>
{
	class DataSet {
	public:
		unsigned short int frameID;
		char padID;
		DataSet() {
			frameID = 0;
			padID = 0;
		}
		DataSet(unsigned short int frameID, char padID) {
			this->frameID = frameID;
			this->padID = padID;
		}
	};

	int _counter;
	float _fps, _recodeFps;
	int _font;
	int _playSpeedID;
	int _frameID, _preChangedFrame;
	PadID _padID;
	int _initPad[PAD_TYPE_NUM];
	int _firstPadStatus[PAD_KEY_NUM];
	int _replayPad[PAD_KEY_NUM];
	int _prePad[PAD_KEY_NUM];
	int _startTime;
	std::vector<DataSet*> _list;
	std::vector<short int> _fpsList;
	int _index;
	FILE* _fp;
	ReplayHeader _header;
	eReplayStatus _status;

public:
	Replayer();
	~Replayer();

	void startRecode(int randSeed, eReplayType type);
	void endRecode(bool recode);
	void clear();
	void recode();

	void die() {
		_header.hitCount++;
	}
	void setStage(eStage stage) {
		_header.stage = stage;
	}
	void setLevel(eLevel level) {
		_header.level = level;
	}
	void bomb() {
		_header.bombCount++;
	}
	void clearStage() {
		_header.clearStageN++;
	}
	bool isRecoding() {
		return _status == eReplayStatus_Recoding;
	}
	bool isReplaying() {
		return _status == eReplayStatus_Replaying;
	}
	void disable() {
		_status = eReplayStatus_Disabled;
	}
	void enable() {
		_status = eReplayStatus_Default;
	}
	bool isDefault() {
		return _status == eReplayStatus_Default;
	}
	int getReplayStage() {
		return _header.stage;
	}
	int getReplayLevel() {
		return _header.level;
	}
	void setFps(float fps) {
		_fps = fps;
	}
	void startReplay(const char *fileName);
	void endReplay();
	void update();
	bool updatePadStatus();
	void draw();
	int getPlaySpeed();
	void setSrand();

};


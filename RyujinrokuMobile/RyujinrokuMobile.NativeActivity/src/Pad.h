#pragma once
#include "Singleton.h"

const static int PAD_KEY_NUM = 16;

enum ePad {
	left, up, right, down, shot, bom, slow, start, change, PAD_TYPE_NUM,
};

class PadID {
public:
//	int left, up, right, down, shot, bom, slow, start, change;
	int padArray[PAD_TYPE_NUM];
};

class Pad : public Singleton<Pad> {

	PadID _padID;
	int pad[PAD_KEY_NUM];
	bool _isReplaying;
public:
	Pad();
	~Pad();
	void initialize();
	void save();
	void update();
	int get(ePad eID);
//	void inputPadData(int *);
//	void registPadData(int *);
	PadID getPadData(){return _padID;}
	void setPadData(PadID pad);
	const int *getPadID() {
		return _padID.padArray;
	}
	const int *getPad() {
		return pad;
	}
	void startReplay(int padArray);
	void setPadStatus(int replayPad[PAD_KEY_NUM]);
};

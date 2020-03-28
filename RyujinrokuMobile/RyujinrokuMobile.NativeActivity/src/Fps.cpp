#include <DxLib.h>
#include "Utils.h"
#include "Fps.h"
#include "Define.h"

#define LIST_LEN_MAX 120	//最大120フレームで待機処理を計算する(2以上にする)
#define FPS 60				//FPS
#define UPINTVL 60			//60フレームに一度更新する

Fps::Fps(){
	_counter = 0;
	_fps = 0.f;
	_font = CreateFontToHandle(FONT, 15, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

Fps::~Fps()
{
	DeleteFontToHandle(_font);
}

void Fps::regist(){
	_list.push_back( GetNowCount() );
	if( _list.size() > LIST_LEN_MAX ){
		_list.pop_front();
	}
}

unsigned Fps::getWaitTime(){
	int sListLen = (int)_list.size();
	if( sListLen == 0 ){
		return 0;
	}
	int sShouldWaitTime = (int)(1000/60.f*(sListLen));
	int sActuallyTookTime = GetNowCount() - _list.front();
	int sWaitTime = sShouldWaitTime - sActuallyTookTime;
	sWaitTime = sWaitTime > 0 ? sWaitTime : 0;
	return (unsigned)(sWaitTime);
}

bool Fps::update(){
	int sListLen = (int)_list.size();
	if( sListLen < LIST_LEN_MAX ){
		return false;
	}
	int sActuallyTookTime = _list.back() - _list.front();
	float fAverage = (float)sActuallyTookTime / (sListLen-1);
	if( fAverage == 0 ){
		return false;
	}
	_fps = round_f( 1000 / fAverage, 2 );
	return true;
}

void Fps::wait(){
	_counter++;
	Sleep( getWaitTime() );
	regist();
	if( _counter % UPINTVL == 0 ){
		update();
		_counter = 0;
	}
}

void Fps::draw(){
	if( _fps == 0 ){
		return ;
	}
	DrawFormatStringToHandle( 1200, 0, GetColor(255,255,255), _font, "%04.1ffps", _fps );
}
